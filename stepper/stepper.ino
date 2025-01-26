#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include "max6675.h"

//Screen
#define TFT_DC 48
#define TFT_CS 53
#define TFT_RST 49
#define TS_CS  46
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TS_CS);

//Heating 
#define RELAYPIN 15

int PWM_pin = 9; 
int set_temperature = 220;            //Default temperature setpoint. Leave it 0 and control it with rotary encoder
float temperature_read = 0.0;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;
float last_set_temperature = 0;
//PID constants
//////////////////////////////////////////////////////////
int kp = 90;   int ki = 15;   int kd = 60;
//////////////////////////////////////////////////////////
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;
const long interval = 250; 

unsigned long previousMillis = 0; 

//Thermocouple
#define MAX6675_CS   47
#define MAX6675_SO   45
#define MAX6675_SCK  44

MAX6675 thermocouple(MAX6675_SCK, MAX6675_CS, MAX6675_SO);
bool isHeating = false;
int tempRead;
float previousTemp = 0.0;

//Motor
unsigned int speed =0;
int previousSpeed = 0;
int motorA = 8;
int motorB = 9;
int motorPWM = A0;

void setup() {
  //screen
  // pinMode(TFT_CS, OUTPUT);
  // pinMode(TS_CS, OUTPUT);
  // digitalWrite(TFT_CS, HIGH);
  // digitalWrite(TS_CS, HIGH);

  //Thermocouple
  // pinMode(MAX6675_CS, OUTPUT);
  // pinMode(MAX6675_SO, INPUT);
  // pinMode(MAX6675_SCK, OUTPUT);
  //digitalWrite(MAX6675_CS, HIGH);
  Time = millis();
  Serial.begin(9600);

  pinMode(RELAYPIN,OUTPUT);
  pinMode(PWM_pin,OUTPUT);

  //screen 
  printUI();
  ts.begin();
  ts.setRotation(1);
  
  writeMotor(speed);
  writeTemp(thermocouple.readCelsius());
  
  //motor
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);


  delay(500);  
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= 1000) {
    Serial.print("C = "); 
    Serial.println(round(thermocouple.readCelsius()));
    temperature_read = round(thermocouple.readCelsius());
    previousMillis = currentMillis; 
    writeTemp(temperature_read);
  }


  if(ts.touched()){
    TS_Point p = ts.getPoint();
    int x = map(p.x, 3936, 410, 0, 320);
    int y = map(p.y, 298, 3876, 0, 240);   
    
    if(x >=50 && x<=50+64 && y >=43 && y <= 43+64){
      if(speed<=0){
        speed = 0;
      }
      else{
        speed--;
      }          
    }
    
    if(x >=210 && x<=210+64 && y >=43 && y <= 43+64){
      if(speed>=5){
        speed = 5;
      }
      else{
        speed++;   
      }
    }
    
    if(x >=136 && x<=136+52 && y>=169 && y<=169+52){
      if(isHeating == false){
        tft.fillRect(136+1, 169+1, 48+2, 48+2, ILI9341_GREENYELLOW);
        tft.setCursor(137+2, 186+2);
        tft.setTextSize(2);
        tft.setTextColor(ILI9341_DARKGREY);
        tft.println("HEAT");   
        digitalWrite(RELAYPIN, HIGH);            
        isHeating = true;
      }  
      else{
        tft.fillRect(136, 169, 48+4, 48+4, ILI9341_BLACK);
        tft.drawRect(136, 169, 48+4, 48+4, ILI9341_WHITE);
        tft.setCursor(137+2, 186+2);
        tft.setTextSize(2);
        tft.setTextColor(ILI9341_DARKGREY);
        tft.println("HEAT"); 
        digitalWrite(RELAYPIN, LOW);   
        isHeating = false;          
      }    
    }
    delay(200);
  }
  
  if(previousSpeed != speed){
    writeMotor(speed);
    previousSpeed = speed;    
  }

  int motor =   map(speed, 0, 5, 128, 255);
  //Serial.println(motor);

  if(speed > 0){
    spinMotor(motor);
  }
  else{
    stopMotor();
  }
  
  //heat();
}

void spinMotor(int pwm){
  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);  
  analogWrite(motorPWM, pwm);
}

void stopMotor(){
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, LOW);  
  analogWrite(motorPWM, 0);
}

void writeTemp(float text){
  String temp = String(text);
  char tempArray[4];
  temp.toCharArray(tempArray, 4);
  //if(text != previousTemp){
    tft.setCursor(50-15, 179);
    tft.setTextSize(4);
    tft.fillRect(50-15, 179, 70, 28, ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);  
    tft.println(tempArray);
    previousTemp = text;
 // }
    
}

void writeMotor(unsigned int speed){
  tft.setCursor(150, 59);
  tft.setTextSize(4);
  tft.fillRect(150, 59, 20, 28, ILI9341_BLACK);
  tft.setTextColor(ILI9341_GREEN);  
  tft.println(speed);
}

void printUI(){
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(72, 5);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(3);
  tft.println("Motor speed");
  tft.setCursor(72, 125);
  tft.println("Nozzle temp");
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_RED);
  tft.setCursor(225, 179);
  tft.println(set_temperature);
  
  tft.drawRect(50, 43, 64, 64, ILI9341_WHITE);
  tft.fillTriangle(104, 53, 60, 76, 104, 97, ILI9341_DARKGREY);
  
  tft.drawRect(210, 43, 64, 64, ILI9341_WHITE);
  tft.fillTriangle(220, 53, 264, 76, 220, 97, ILI9341_DARKGREY);

  tft.drawRect(136, 169, 48+4, 48+4, ILI9341_WHITE);
  tft.setCursor(137+2, 186+2);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.println("HEAT");
}

void heat(){
  unsigned long currentMillis = millis();
 
 // if(currentMillis - previousMillis1 > interval) {
    // save the last time you blinked the LED 
    //previousMillis1 = currentMillis;   
    //temperature_read = thermocouple.readCelsius();
  //Next we calculate the error between the setpoint and the real value
    PID_error = set_temperature - temperature_read + 3;
    //Calculate the P value
    PID_p = 0.01*kp * PID_error;
    //Calculate the I value in a range on +-3
    PID_i = 0.01*PID_i + (ki * PID_error);
    

    //For derivative we need real time to calculate speed change rate
    timePrev = Time;                            // the previous time is stored before the actual time read
    Time = millis();                            // actual time read
    elapsedTime = (Time - timePrev) / 1000; 
    //Now we can calculate the D calue
    PID_d = 0.01*kd*((PID_error - previous_error)/elapsedTime);
    //Final total PID value is the sum of P + I + D
    PID_value = PID_p + PID_i + PID_d;

    //We define PWM range between 0 and 255
    if(PID_value < 0)
    {    PID_value = 0;    }
    if(PID_value > 255)  
    {    PID_value = 255;  }
    //Now we can write the PWM signal to the mosfet on digital pin D3
    //Since we activate the MOSFET with a 0 to the base of the BJT, we write 255-PID value (inverted)
    analogWrite(PWM_pin,255-PID_value);
    previous_error = PID_error;     //Remember to store the previous error for next loop.
  //}
}