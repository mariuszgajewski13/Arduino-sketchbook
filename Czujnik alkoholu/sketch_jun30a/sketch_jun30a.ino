#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int analog = A0;
int buttonpin = 9;
int buttonState = 0;

int test;
int testSuma;
int wynik;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  pinMode(analog, INPUT);
  pinMode(buttonpin, INPUT);

  
  display.setCursor(0, 0);
  Serial.println("Kalibracja...");
  for(int i=0;i<10;i++){
    test = analogRead(analog);
    Serial.println(test);
    testSuma+=test;
    delay(500);
  }
  wynik=testSuma/10;
  Serial.print("Test: ");
  Serial.println(wynik);
  display.print("TEST: ");
  display.print(test);
  Serial.println("Zakonczono test");
  Serial.println("PUSH");
  display.setCursor(54, 20);
  display.print("PUSH");
}

void loop() {
  int value = analogRead (analog);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  //buttonState = digitalRead(buttonpin);
  int count =0, suma=0;
  float avg, promile, alko;
  
  if(digitalRead(buttonpin)== HIGH){
    delay(50); 
    for(int i=0;i<10;i++){
      value = analogRead(analog);
      Serial.println(value);
      suma+=value;
      delay(400);
    }
    count++;
  }

  if(count>0){
    avg=suma/10;
    alko = (avg - wynik)/1000;
    promile = alko * 2,1;
    display.clearDisplay();
    display.print("Test: ");
    display.print(test);
    display.setCursor(57, 20);
    Serial.println("Wynik: ");
    Serial.println(avg);
    display.print("W ");
    display.print(avg);
    display.setCursor(60, 20);
    Serial.println("mg/l: ???");
    Serial.println(alko);
    display.print("W-T ");
    display.print(alko);
    display.setCursor(63, 20);
    Serial.println("Promile: ???");
    Serial.print(promile);
    Serial.print(" ‰");
    display.print("P ");
    display.print(promile);
    delay(5000);
  }
  

}


int pomiar(){
  int value, suma=0, alko;
  for(int i=0;i<5;i++){
    value = analogRead(analog);
    //Serial.println(value);
    suma+=value;
  }
  alko=suma/5;
  
  Serial.println(alko);
}

void nagrzewanie(){
  Serial.println("Nagrzewanie (60s)");
  for(int i=0;i<60;i++){
    Serial.println(i);
    delay(1000);
  }
  Serial.println("Zakonczono nagrzewanie");
}

int pomiartest(){
 int test;
  int testSuma;
  int wynik;
  Serial.println("Kalibracja...");
  for(int i=0;i<10;i++){
    test = analogRead(analog);
    Serial.println(test);
    testSuma+=test;
    delay(500);
  }
  wynik=testSuma/10;
  Serial.print("Test: ");
  Serial.println(wynik);
  Serial.println("Zakonczono test");
  return wynik;
}
