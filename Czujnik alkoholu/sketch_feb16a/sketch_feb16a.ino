#include <LiquidCrystal_I2C.h>
int buttonpin = 9;
int buttonState = 0;
int ledPin = 13;
int sensorPin = A0;

int test;
int testSuma;
int wynik;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  Serial.begin(9600);
  pinMode(buttonpin, INPUT);
  pinMode(ledPin, OUTPUT);

  nagrzewanie();

  lcd.begin(16, 2);   
  lcd.backlight(); 
  lcd.setCursor(0,0);
  
  Serial.println("Kalibracja...");
  for(int i=0;i<10;i++){
    test = analogRead(sensorPin);
    Serial.println(test);
    testSuma+=test;
    delay(500);
  }
  wynik=testSuma/10;
  Serial.print("Test: ");
  Serial.println(wynik);
  lcd.print("TEST: ");
  lcd.print(test);
  Serial.println("Zakonczono test");
  Serial.println("PUSH");
  lcd.setCursor(0, 1);
  lcd.print("PUSH");
}

void loop() {
  //buttonState = digitalRead(buttonpin);
  int count =0, value, suma=0;
  float avg, promile, alko;
  
  if(digitalRead(buttonpin)== HIGH){
    delay(50); 
    for(int i=0;i<10;i++){
      value = analogRead(sensorPin);
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T ");
    lcd.print(test);
    lcd.setCursor(9, 0);
    Serial.println("Wynik: ");
    Serial.println(avg);
    lcd.print("W ");
    lcd.print(avg);
    lcd.setCursor(0, 1);
    Serial.println("mg/l: ???");
    Serial.println(alko);
    lcd.print("W-T ");
    lcd.print(alko);
    lcd.setCursor(9, 1);
    Serial.println("Promile: ???");
    Serial.print(promile);
    Serial.print(" ‰");
    lcd.print("P ");
    lcd.print(promile);
    delay(5000);
  }
  
}

int pomiar(){
  int value, suma=0, alko;
  for(int i=0;i<5;i++){
    value = analogRead(sensorPin);
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
    test = analogRead(sensorPin);
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
