#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int AIA = 2;  // (pwm) pin connected to pin A1
const int AIB = 3;  // (pwm) pin connected to pin A2
const int BIA = 4; // (pwm) pin connected to pin B1
const int BIB = 5;  // (pwm) pin connected to pin B2
//byte speed = 50;  // change this (0-255) to control the speed of the motors
int values[2];
RF24 radio(8,9); // CE, CSN
const byte address[6] = "00001";

int serwo = 6;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address); 
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.begin(9600);
  pinMode(serwo, OUTPUT);
  digitalWrite(serwo, LOW);
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
      radio.read(&values, sizeof(values));
      
      int speedValue = values[0];
      int angleValue = values[1];
      Serial.print(speedValue);
      Serial.print("\t");
      Serial.print(angleValue);
      Serial.println();
      
      digitalWrite(serwo, HIGH);
      delayMicroseconds(angleValue);
      digitalWrite(serwo, LOW);
      delay(20);
      
      if(speedValue > 0){
        forward(speedValue);
        //Serial.println(speedValue);
      }
       else if(speedValue <0){
        speedValue = -speedValue;
        backward(speedValue);
        //Serial.println(speedValue);
       }
    
    delay(5);
  }

}

void backward(int speedValue)
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speedValue);
  analogWrite(BIA, 0);
  analogWrite(BIB, speedValue);
}

void forward(int speedValue)
{
  analogWrite(AIA, speedValue);
  analogWrite(AIB, 0);
  analogWrite(BIA, speedValue);
  analogWrite(BIB, 0);
}
void left(int speedValue)
{
  analogWrite(AIA, speedValue);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speedValue);
}
void right(int speedValue)
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speedValue);
  analogWrite(BIA, speedValue);
  analogWrite(BIB, 0);
}
void STOP(int speedValue)
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  delay (2000);
}
