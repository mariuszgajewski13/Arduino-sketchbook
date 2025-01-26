#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

const int ledpin = 6;
const int numLeds = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledpin, NEO_GRB + NEO_KHZ800);

SoftwareSerial mySerial(2,3);


void setup()  
{

  mySerial.begin(9600);
  Serial.begin(9600);
  //pinMode(ledpin,OUTPUT);

  strip.begin();
  strip.setBrightness(200);
  //white();
  //rainbow1();
  //off();
}

void loop() 
{
  int i;

  if (mySerial.available()){
    i=mySerial.read();
    //Serial.println("DATA RECEIVED:");
    //lcd.print(i);

    switch(i){
      case '1': rainbow1();
                break;
           
      case '2': white();
                break;
            
      case '0': off();
                break;
    
      default: //while(1==1)
               //rainbow1(20);
               break;
     }
  }
}

void rainbow1() {
  for (long firstPixelHue = 0; ; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(20);
  } 
}

void white() {
  uint32_t color = strip.Color(250, 250, 250);
  strip.fill(color);
  strip.show();
}

void off(){
  strip.clear();
  strip.show();
}
