// int analogPin = 0;
// int raw = 0;
// int Vin = 5;
// float Vout = 0;
// float R = 250;
// float R1 = 0;
// float buffer = 0;

// int analogPin1 = 1;
// int raw1 = 0;
// float V1out = 0;
// float R2 = 0;
// float buffer1 = 0;

int led1 = 9;
int led2 = 10;


// int leftButtonState = 0;        // current state of the button
// int rightButtonState = 0;        // current state of the button       

// int leftLastButtonState = 0;    // previous state of the button
// int rightLastButtonState = 0;    // previous state of the button

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

}

void loop(){
  raw = analogRead(analogPin);

  if(raw != leftLastButtonState){
    raw = analogRead(analogPin);

    buffer = raw * Vin;
    Vout = (buffer)/1024.0;
    buffer = (Vin/Vout) - 1;
    R1= R * buffer;
    if(R1 < 100){
      //Serial.print("R1: ");
      //Serial.println(R1);
      Serial.println(1);

      digitalWrite(led1, HIGH);
    }
    else
      digitalWrite(led1, LOW);
  }
  leftLastButtonState = raw;

  raw1 = analogRead(analogPin1);
  buffer1 = raw1 * Vin;
  V1out = (buffer1)/1024.0;
  buffer1 = (Vin/V1out) - 1;
  R2= R * buffer1;
  if(R2 < 100){
    //Serial.print("R2: ");
    //Serial.println(R2);
    Serial.println(2);

    digitalWrite(led2, HIGH);
  }
  else
    digitalWrite(led2, LOW);
  

}