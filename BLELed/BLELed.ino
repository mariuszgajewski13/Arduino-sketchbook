#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //TX, RX(dzielnik napięcia)
int ledpin = 9;

void setup() {
  mySerial.begin(9600);
  pinMode(ledpin, OUTPUT);
}

void loop() {
  int i;

  if (mySerial.available()){
    i = mySerial.read();
    
    if (i == '1'){
      digitalWrite(ledpin,HIGH);
    }
    if (i == '0'){
      digitalWrite(ledpin, LOW);
    }
  }
}
