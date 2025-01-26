#include <Adafruit_NeoPixel.h>

const int ledpin = 6;
const int numLeds = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledpin, NEO_GRB + NEO_KHZ800);

int MicSensor = 8; 
//int LED = 6 ; 

void setup() 
{
  Serial.begin(9600);

  pinMode (MicSensor, INPUT); // sensor pin INPUT
 // pinMode (LED, OUTPUT); // Led pin OUTPUT

  strip.begin();
  strip.setBrightness(200);
}

int count = 0;

void loop()
{
  int statusSensor = digitalRead (MicSensor);
  //Serial.println(statusSensor);
  if (statusSensor == 0){
    //digitalWrite(LED, HIGH); 
    white();
    ++count;
    Serial.println(count);
    delay(50);
    if(count>=2){
      //digitalWrite(LED, LOW);
      off();
      count=0;
    }
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
