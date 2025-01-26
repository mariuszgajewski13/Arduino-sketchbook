#include <Stepper.h>

const int stepsPerRevolution = 2048; 

Stepper stepper(stepsPerRevolution, 8, 10, 9, 11);

const int buttonUp =  6;
const int buttonDown =  5; 

int speed = 50;

void setup()
{
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  while ( digitalRead(buttonUp) == 0 ) 
  {
    stepper.setSpeed(speed);
    Serial.println("Up");
    stepper.step(1);
  }
  while ( digitalRead(buttonDown) == 0 ) 
  {
    stepper.setSpeed(speed);
    Serial.println("Down");
    stepper.step(-1);
  }
}