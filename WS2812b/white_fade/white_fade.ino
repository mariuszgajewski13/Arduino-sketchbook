#include <Adafruit_NeoPixel.h>

const int ledPin = 6;
const int numLeds = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(100);
}

void loop() {
  
  for(int i=50;i<150;i++){
    uint32_t color = strip.Color(i, i, i);
    strip.fill(color);
    delay(10);
    strip.show();
  }
  for(int i=150;i>50;i--){
    uint32_t color = strip.Color(i, i, i);
    strip.fill(color);
    delay(10);
    strip.show();
  }
  
  
}
