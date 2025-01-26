#include <Adafruit_NeoPixel.h>

const int ledPin = 6;
const int numLeds = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(50);
}

void loop() {
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue+=128) {
      strip.fill(strip.gamma32(strip.ColorHSV(firstPixelHue)));
      strip.show();
      delay(20);
    }
}
