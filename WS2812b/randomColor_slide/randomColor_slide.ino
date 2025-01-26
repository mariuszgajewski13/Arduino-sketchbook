#include <Adafruit_NeoPixel.h>

const int ledPin = 2;
const int numLeds = 600;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(20);  
}


void loop() {
  uint32_t white = strip.Color(200, 200, 200);
  uint32_t randomColor;
  
  randomColor = strip.gamma32(strip.ColorHSV(random(0,65536)));   
  for(int i=0;i<numLeds;i++) {
      strip.fill(0);
      strip.show();
      //randomColor = strip.gamma32(strip.ColorHSV(random(0,65536)));
      strip.setPixelColor(i, randomColor);
      strip.setPixelColor(i+1, randomColor);
      strip.setPixelColor(i+2, randomColor);
      strip.show();
      delay(50);
    }
    
    randomColor = strip.gamma32(strip.ColorHSV(random(0,65536)));
    for(int i=numLeds;i>0;i--) {
      strip.fill(0);
      strip.show();
      //randomColor = strip.gamma32(strip.ColorHSV(random(0,65536)));
      strip.setPixelColor(i, randomColor);
      strip.setPixelColor(i-1, randomColor);
      strip.setPixelColor(i-2, randomColor);
      strip.show();
      delay(50);
    }
}
