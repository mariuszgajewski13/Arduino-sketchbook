#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10); // CE, CSN
const byte 
address[6] = "00001";
const int gasPin = 6;
const int breakPin = 7;
int values[3];

void setup() {
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
  pinMode(gasPin, INPUT);
  pinMode(breakPin, INPUT);
}

void loop() {
  delay(5);
  radio.stopListening();
  //int xValue = analogRead(A0);
  int yValue = analogRead(A1);
  int gasState = digitalRead(gasPin);
  int breakState = digitalRead(breakPin);
  //Serial.println(xValue);
  //int speedValue = map(xValue, 507, 1023, 0, 250);
  int angleValue = map(yValue, 0, 1023, 1000, 400);
  Serial.print(gasState);
  Serial.print("\t");
  Serial.print(breakState);
  Serial.print("\t");
  Serial.print(angleValue);
  Serial.println();
  values[0] = gasState;
  values[1] = breakState;
  values[2] = angleValue;
  radio.write(&values, sizeof(values));
  delay(5);
}
