// G connect to GND
// + connect to 5V
// L connect pin 6(1st module) & 5(2nd module)
// S connect pin 7(1st module) & 4(2nd module)
int LedPinA = 5;
int LedPinB = 6;
int ButtonPinA = 7;
int ButtonPinB = 4;
int buttonStateA = 0;
int buttonStateB = 0;
int brightness = 0;
void setup ()
{
  pinMode (LedPinA, OUTPUT);
  pinMode (LedPinB, OUTPUT);
  pinMode (ButtonPinA, INPUT);
  pinMode (ButtonPinB, INPUT);
}
void loop ()
{
  buttonStateA = digitalRead (ButtonPinA);
  if (buttonStateA == HIGH && brightness != 255)
  {
    brightness += 1;
  }
  buttonStateB = digitalRead (ButtonPinB);
  if (buttonStateB == HIGH && brightness != 0)
  {
    brightness -= 1;
  }
  analogWrite (LedPinA, brightness); // A few Guan Yuan (ii) ? 
  analogWrite (LedPinB, 255 - brightness);// B Yuan (ii) a few Bang ?
  delay (25);
}
