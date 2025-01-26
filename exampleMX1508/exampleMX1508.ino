const int AIA = 5;  // (pwm) pin 5 connected to pin A1
const int AIB = 6;  // (pwm) pin 6 connected to pin A2
const int BIA = 9; // (pwm) pin 10 connected to pin B1
const int BIB = 10;  // (pwm) pin 11 connected to pin B2
byte speed = 255;  // change this (0-255) to control the speed of the motors
void setup() {
  pinMode(AIA, OUTPUT); // set pins to output
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  Serial.begin( 9600 );
}
void loop() {
  Serial.println( "Avanti..." );
  forward();
  delay(2000);
  STOP();
  Serial.println( "Indietro..." );
  backward();
  delay(2000);
  STOP();
  Serial.println( "Sinistra..." );
  left();
  delay(2000);
  STOP();
  Serial.println( "Destra..." );
  right();
  delay(2000);
  STOP();
}
void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void STOP()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  delay (2000);
}
