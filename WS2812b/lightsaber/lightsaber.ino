#include <Adafruit_NeoPixel.h>

const int ledPin = 7;
const int numLeds = 14;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.setBrightness(20);
  strip.begin();
}

void loop() {
  uint32_t color = strip.gamma32(strip.ColorHSV(21000));
  for(int i=0;i<numLeds;i++){
    strip.setPixelColor(i, color);
    strip.show();
    delay(20);
  }
}
