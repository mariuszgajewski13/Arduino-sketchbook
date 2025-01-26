#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int AIA = 2;  // (pwm) pin connected to pin A1
const int AIB = 3;  // (pwm) pin connected to pin A2
const int BIA = 4; // (pwm) pin connected to pin B1
const int BIB = 5;  // (pwm) pin connected to pin B2
//byte speed = 50;  // change this (0-255) to control the speed of the motors
int values[3];
RF24 radio(39,22); // CE, CSN
const byte address[6] = "00001";
int serwo = 33;


void setup() {
  radio.begin();
  radio.openReadingPipe(0, address); 
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);
  pinMode(serwo, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(serwo, LOW);
}

void loop() {
  radio.startListening();
  if ( radio.available()) {
      radio.read(&values, sizeof(values));
      
      int speedValue = 0;
      int gasState = values[0];
      int breakState = values[1];
      int angleValue = values[2];
          
      Serial.print(gasState);
      Serial.print("\t");
      Serial.print(breakState);
      Serial.print("\t");
      Serial.print(angleValue);
      Serial.println();


      int filtr=0.98;
      int angleV;

     angleV = filtr * angleV+(1-filtr)*angleValue;
     
     digitalWrite(serwo, HIGH);
     delayMicroseconds(angleV);
     digitalWrite(serwo, LOW);
     delay(20);


     if(gasState == 0 and breakState == 0){
       STOP();
       Serial.print("STOP");
      Serial.print("\t");
      Serial.print(angleValue);
      Serial.println();
     }
     else if(gasState == 1 and breakState == 0){
       forward(200);
       Serial.print("FORWARD");
       Serial.print("\t");
       Serial.print(angleValue);
       Serial.println();
     }
     else if(gasState == 0 and breakState == 1){
       backward(200);
       Serial.print("BACKWARD");
       Serial.print("\t");
       Serial.print(angleValue);
       Serial.println();
     }
      t0
     if(speedValue > 0){
       forward(speedValue);
       //Serial.println(speedValue);
     }
      else if(speedValue <0){
       speedValue = -speedValue;
       backward(speedValue);
       //Serial.println(speedValue);
      }
  }
  else{
    Serial.println("NOT CONNECTED!");
  }
}

void backward(int speedValue)
{
  analogWrite(AIA, speedValue);
  analogWrite(AIB, 0);
  analogWrite(BIA, speedValue);
  analogWrite(BIB, 0);
}

void forward(int speedValue)
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speedValue);
  analogWrite(BIA, 0);
  analogWrite(BIB, speedValue);
  
}
void left(int speedValue)
{
  analogWrite(AIA, speedValue);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speedValue);
}
void right(int speedValue)
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speedValue);
  analogWrite(BIA, speedValue);
  analogWrite(BIB, 0);
}
void STOP()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}
