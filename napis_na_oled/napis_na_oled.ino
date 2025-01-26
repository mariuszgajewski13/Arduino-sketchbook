#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const unsigned char myBitmap [] PROGMEM = {
  // 'Blow_Kiss_Emoji_large, 25x25px
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xf0, 0x00, 
  0x0f, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x3e, 0xff, 0xfc, 0x00, 0x39, 0xff, 0xfe, 0x00, 
  0x73, 0xff, 0x7e, 0x00, 0x77, 0xfe, 0x0e, 0x00, 0x7f, 0x3f, 0xff, 0x00, 0xfe, 0x3e, 0x7f, 0x00, 
  0xfe, 0x3c, 0x3f, 0x00, 0xff, 0x7f, 0xff, 0x00, 0x7f, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xc6, 0x00, 
  0x7f, 0xfd, 0x80, 0x00, 0x3f, 0xf8, 0x80, 0x00, 0x3f, 0xf9, 0xc0, 0x00, 0x1f, 0xfd, 0xc0, 0x00, 
  0x0f, 0xfc, 0xe0, 0x00, 0x07, 0xfb, 0xe0, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
};

byte customChar[8] ={
                      B00000,
                      B01110,
                      B00001,
                      B01111,
                      B10001,
                      B01111,
                      B00010,
                      B00001
                     };

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(25, 0);
  display.println("Paczek!");
  // Display static text
  //display.print("P");
  //display.drawBitmap(31, 0, customChar, 5, 8, WHITE);
  //display.setCursor(37, 0);
  //display.print("czek!");
  display.drawBitmap(54, 20, myBitmap, 25, 25, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
}


void loop() {
  
}
