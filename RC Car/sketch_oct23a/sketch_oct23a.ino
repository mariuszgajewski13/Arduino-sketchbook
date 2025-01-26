#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10); // CE, CSN
const byte address[6] = "00001";
int values[2];
void setup() {
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  delay(5);
  radio.stopListening();
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);
  //Serial.println(xValue);
  int speedValue = map(xValue, 507, 1023, 0, 250);
  int angleValue = map(yValue, 0, 1023, 3000, 0);
  Serial.print(speedValue);
  Serial.print("\t");
  Serial.print(angleValue);
  Serial.println();
  values[0] = speedValue;
  values[1] = angleValue;
  radio.write(&values, sizeof(values));
  delay(5);
}
