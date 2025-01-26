#include <Adafruit_NeoPixel.h>

const int ledPin1 = 7;
const int ledPin2 = 8;
const int numLeds = 15;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(numLeds, ledPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numLeds, ledPin2, NEO_GRB + NEO_KHZ800);

void setup() {
  strip1.begin();
  strip1.setBrightness(200);
  strip2.begin();
  strip2.setBrightness(200);
}

void loop() {
  rainbow11(20);
  //rainbow12(20);

  //rainbow2(20);

  //rainbow3(20);

}

void rainbow11(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < numLeds; i++) {
      int pixelHue = firstPixelHue + (i * 65536L / numLeds);
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
      strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
    }
    strip1.show();
    strip2.show();
    delay(wait);
  }
}
//
//void rainbow12(int wait) {
//  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
//    for (int i = 0; i < strip2.numPixels(); i++) {
//      int pixelHue = firstPixelHue + (i * 65536L / strip2.numPixels());
//      strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
//    }
//    strip2.show();
//    delay(wait);
//  }
//}

//void rainbow2(uint8_t wait) {
//  uint16_t i, j;
//
//  for (j = 0; j < 256; j++) {
//    for (i = 0; i < strip1.numPixels(); i++) {
//      strip1.setPixelColor(i, Wheel((i + j) & 255));
//    }
//    strip1.show();
//    delay(wait);
//  }
//}
//
//void rainbow3(uint8_t wait) {
//  uint16_t i, j;
//
//  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
//    for (i = 0; i < strip1.numPixels(); i++) {
//      strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
//    }
//    strip1.show();
//    delay(wait);
//  }
//}
//
//uint32_t Wheel(byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if (WheelPos < 85) {
//    return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if (WheelPos < 170) {
//    WheelPos -= 85;
//    return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}
