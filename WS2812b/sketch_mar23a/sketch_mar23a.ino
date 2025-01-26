#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

#define DECODE_NEC 1
int IR_RECEIVE_PIN = 11;
//const int ledPin1 = 6;
const int ledPin2 = 7;
const int numLeds = 14;

//Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(14, ledPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(13, ledPin2, NEO_GRB + NEO_KHZ800);

void setup() {
  //  strip1.begin();
  //  strip1.setBrightness(250);
  strip.begin();
  strip.setBrightness(200);
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    IrReceiver.resume();
    int data = IrReceiver.decodedIRData.command;
    
    switch(data){
      case 0x45:
        //Serial.println(data);
        rainbow();
        break;
      case 0x47:
        //Serial.println(data);
        black();
        break;
      case 0xC:
        red();
        break;
      case 0x18:
        green();
        break;
      case 0x5E:
        blue();
        break;
      case 0x8:
        white();
        break;
      case 0x1C:
        color1();
        break;
      case 0x5A:
        color2();
        break;
      case 0x42:
        color3();
        break;
    }
  }
}

void rainbow() {
    uint16_t i;
    for(int j=0; ; j++) { 
      for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      //Serial.println(IrReceiver.decodedIRData.command);
      strip.show();
      if (IrReceiver.decode()) {
        if(IrReceiver.decodedIRData.command == 0)
          black();
          break;
      }
      delay(20);
    }
}

uint32_t Wheel(byte WheelPos) {
    if (WheelPos < 85) {
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

void black() {
  strip.clear();
  strip.show();
}

void red() {
  uint32_t red = strip.gamma32(strip.Color(255, 0, 0));
  strip.fill(red);
  strip.show();
}

void green() {
  uint32_t green = strip.gamma32(strip.Color(0, 255, 0));
  strip.fill(green);
  strip.show();
}

void blue() {
  uint32_t blue = strip.gamma32(strip.Color(0, 0, 255));
  strip.fill(blue);
  strip.show();
}

void white() {
  uint32_t white = strip.gamma32(strip.Color(255, 255, 255));
  strip.fill(white);
  strip.show();
}

void color1() {
  uint32_t color = strip.gamma32(strip.Color(50, 30, 155));
  strip.fill(color);
  strip.show();
}

void color2() {
  uint32_t color = strip.gamma32(strip.Color(250, 0, 255));
  strip.fill(color);
  strip.show();
}

void color3() {
  uint32_t color = strip.gamma32(strip.Color(100, 0, 200));
  strip.fill(color);
  strip.show();
}
