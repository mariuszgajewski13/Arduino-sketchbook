#include <Adafruit_NeoPixel.h>

const int ledPin = 6;
const int ledPin1 = 7;
const int numLeds1 = 14;
const int numLeds2 = 13;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds1, ledPin, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(numLeds2, ledPin1, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(100);

  strip1.begin();
  strip1.setBrightness(200);
}

void loop() {
  uint32_t color = strip.Color(255, 255, 255);
  
  strip.fill(color);
  strip.show();
  
  strip1.fill(color);
  strip1.show();

}
