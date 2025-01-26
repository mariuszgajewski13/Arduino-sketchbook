#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

const int ledPin = 6;
const int numLeds = 15;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define trigPin 4
#define echoPin 5


void setup() {
  Serial.begin (9600);
  strip.begin();
  strip.setBrightness(100);

  lcd.begin(16, 2);   
  lcd.backlight(); 
  lcd.setCursor(0,0);
  lcd.print("Dystans[cm]: ");
 
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop() {
  leds();

  lcd.setCursor(0,1);  
  lcd.print("                ");
  lcd.setCursor(0,1);   
  lcd.print(distance());
  delay(250);
  
}

int distance() {
  long czas, dystans;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  czas = pulseIn(echoPin, HIGH);
  dystans = czas *0.034/2;
 
  return dystans;
}
 
void leds() {
  int cm = distance();
  if ((cm >= 0) && (cm < 15)) {
      strip.fill(strip.Color(255, 0, 0));
      strip.show();
  } 
  else if((cm >= 15) && (cm < 30)) {
      strip.fill(strip.Color(255, 255, 0));
      strip.show();
  }   
  else{
      strip.fill(strip.Color(0, 255, 0));
      strip.show();
  }
}
