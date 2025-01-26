#include "LowPower.h"
#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

dht DHT;

#define DHT11_PIN 7
const int wakeUpPin = 2;

void wakeUp()
{
   
}

void setup()
{
    pinMode(wakeUpPin, INPUT); 
    pinMode(DHT11_PIN, INPUT);  
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    lcd.backlight();
    lcd.init();
}

void loop() 
{
    digitalWrite(4, LOW);
    attachInterrupt(0, wakeUp, HIGH);
    
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
   // if(digitalRead(wakeUpPin) == HIGH)
     // check();
digitalWrite(4, HIGH);
    int chk = DHT.read11(DHT11_PIN);
    lcd.setCursor(0,0); 
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    delay(1000);   
    detachInterrupt(0); 
    
                                             
}

void check(){
    digitalWrite(4, HIGH);
    int chk = DHT.read11(DHT11_PIN);
    lcd.setCursor(0,0); 
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    delay(1000);   
}
