#include <Adafruit_NeoPixel.h>

const int ledPin1 = 8;
const int ledPin2 = 7;
const int numLeds = 30;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(numLeds, ledPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numLeds, ledPin2, NEO_GRB + NEO_KHZ800);

void setup() {
  strip1.begin();
  strip1.setBrightness(250);
  strip2.begin();
  strip2.setBrightness(250);
}

void loop() {
  for(int i=0;i<numLeds;i++){
    if(i%2==0){
      strip1.setPixelColor(i, strip1.gamma32(strip1.Color(255, 0, 0)));
      strip2.setPixelColor(i, strip1.gamma32(strip1.Color(255, 0, 0)));
      strip1.show();
      strip2.show();
    }
    else{
      strip1.setPixelColor(i, strip1.gamma32(strip1.Color(0, 255, 0)));
      strip2.setPixelColor(i, strip1.gamma32(strip1.Color(0, 255, 0)));
      strip1.show();
      strip2.show();
    } 
    
  }
  delay(1000);
  for(int i=0;i<numLeds;i++){
    if(i%2!=0){
      strip1.setPixelColor(i, strip1.gamma32(strip1.Color(255, 0, 0)));
      strip2.setPixelColor(i, strip1.gamma32(strip1.Color(255, 0, 0)));
      strip1.show();
      strip2.show();
    }
    else{
      strip1.setPixelColor(i, strip1.gamma32(strip1.Color(0, 255, 0)));
      strip2.setPixelColor(i, strip1.gamma32(strip1.Color(0, 255, 0)));
      strip1.show();
      strip2.show();
    } 
  }
  delay(1000); 
}
