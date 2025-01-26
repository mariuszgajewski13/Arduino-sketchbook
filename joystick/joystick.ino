int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = 3; // key

void setup (){
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT_PULLUP);
  Serial.begin (9600); // 9600 bps
}

void loop (){
  int x, y, z;
  x = analogRead (JoyStick_X);
  y = analogRead (JoyStick_Y);
  z = digitalRead (JoyStick_Z);
  Serial.print (x);
  Serial.print (",");
  Serial.print (y);
  Serial.print (",");
  Serial.println (z);
  delay (100);
}

                    
