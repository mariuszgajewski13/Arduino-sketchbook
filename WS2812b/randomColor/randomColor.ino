#include <Adafruit_NeoPixel.h>

const int ledPin = 7;
const int numLeds = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(20);
}

void loop() {
  uint32_t randomColor;
 
  randomColor = strip.ColorHSV(random(0,65536));
  strip.fill(randomColor);
  delay(500);
   
   strip.show();
}
