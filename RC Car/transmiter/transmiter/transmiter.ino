#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10); // CE, CSN
const byte address[6] = "00001";
const int gasPin = 6;
const int breakPin = 7;
int values[3];

void setup() {
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);
  //radio.stopListening();
  Serial.begin(9600);
  pinMode(gasPin, INPUT);
  pinMode(breakPin, INPUT);
}

void loop() {
  delay(5);
  radio.stopListening();
  int yValue = analogRead(A1);
  int gasState = digitalRead(gasPin);
  int breakState = digitalRead(breakPin);
  
  int angleValue = map(yValue, 0, 1023, 1000, 400);
//  int angleValue=0;
//
//  if(yValue > 500 && yValue < 530)
//    angleValue = 0;
//  else if(yValue >= 530)
//    angleValue = 1;
// else if(yValue <= 500)
//    angleValue = 2;
 
  Serial.print(gasState);
  Serial.print("\t");
  Serial.print(breakState);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print("\t");
  Serial.print(angleValue);
  Serial.println();
  
  values[0] = gasState;
  values[1] = breakState;
  values[2] = angleValue;
  radio.write(&values, sizeof(values));
  delay(5);
}
