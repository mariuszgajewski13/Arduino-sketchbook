#include <LiquidCrystal_I2C.h>

int digital = 8;
int analog = 0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  pinMode(digital, INPUT);

  lcd.begin(16, 2);   
  lcd.backlight(); 
  lcd.setCursor(0,0);
  lcd.print("Alkohol: ");
}

void loop() {
  int value = analogRead (analog);
  Serial.println(value);

  lcd.setCursor(0,1);  
  lcd.print("                ");
  lcd.setCursor(0,1);   
  lcd.print(value);
  delay(250);

}
