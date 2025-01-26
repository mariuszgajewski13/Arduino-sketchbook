#include <Adafruit_NeoPixel.h>

const int ledPin = 2;
const int numLeds = 600;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.setBrightness(20);
  uint32_t randomColor;
  int i=0;
  while(i<numLeds){
    randomColor = strip.gamma32(strip.ColorHSV(random(0,65536/6)));
    //randomColor = strip.gamma32(strip.Color(random(1,255), random(1,255), random(1,255)));
    strip.setPixelColor(i, randomColor);
    strip.show();
    i++;
  }
  strip.begin();
}

void loop() {
  uint32_t randomColor;
  int i=random(0,numLeds);
  randomColor = strip.gamma32(strip.ColorHSV(random(0,65536)));
  strip.setPixelColor(i, randomColor);
  strip.show();
  delay(100);   
}
