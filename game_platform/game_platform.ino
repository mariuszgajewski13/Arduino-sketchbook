#define powerLED 3
int delayValue = 50;

//Player 1
#define leftPin1 6
#define rightPin1 7

int ledLeft1 = 13;
int ledRight1 = 12;

int left1ButtonState = 0;
int lastLeft1ButtonState = 0;

int right1ButtonState = 0;
int lastRight1ButtonState = 0;

//Player 2
#define leftPin2 4
#define rightPin2 5

int ledLeft2 = 9;
int ledRight2 = 10;

int left2ButtonState = 0;
int lastLeft2ButtonState = 0;

int right2ButtonState = 0;
int lastRight2ButtonState = 0;

void setup(){
  Serial.begin(9600);
  pinMode(powerLED, OUTPUT);
  digitalWrite(powerLED, HIGH);

  //Player 1
  pinMode(ledLeft1, OUTPUT);
  pinMode(ledRight1, OUTPUT);
  pinMode(leftPin1, INPUT_PULLUP);
  pinMode(rightPin1, INPUT_PULLUP);

  //Player 2
  pinMode(ledLeft2, OUTPUT);
  pinMode(ledRight2, OUTPUT);
  pinMode(leftPin2, INPUT_PULLUP);
  pinMode(rightPin2, INPUT_PULLUP);

}

void loop(){
  //Player 1
  left1ButtonState = digitalRead(leftPin1);
  if(left1ButtonState != lastLeft1ButtonState){
    if(left1ButtonState == LOW){
      Serial.println(1);
      digitalWrite(ledLeft1, HIGH);
    }
    else{
      Serial.println();
      digitalWrite(ledLeft1, LOW);
    }
    delay(delayValue);
  lastLeft1ButtonState = left1ButtonState;
  }

  right1ButtonState = digitalRead(rightPin1);
  if(right1ButtonState != lastRight1ButtonState){
    if(right1ButtonState == LOW){
      Serial.println(2);
      digitalWrite(ledRight1, HIGH);
    }
    else{
      Serial.println();
      digitalWrite(ledRight1, LOW);
    }
    delay(delayValue);
  lastRight1ButtonState = right1ButtonState;
  }
  
  //Player 2
  left2ButtonState = digitalRead(leftPin2);
  if(left2ButtonState != lastLeft2ButtonState){
    if(left2ButtonState == LOW){
      Serial.println(3);
      digitalWrite(ledLeft2, HIGH);
    }
    else{
      Serial.println();
      digitalWrite(ledLeft2, LOW);
    }
    delay(delayValue);
  lastLeft2ButtonState = left2ButtonState;
  }

  right2ButtonState = digitalRead(rightPin2);
  if(right2ButtonState != lastRight2ButtonState){
    if(right2ButtonState == LOW){
      Serial.println(4);
      digitalWrite(ledRight2, HIGH);
    }
    else{
      Serial.println();
      digitalWrite(ledRight2, LOW);
    }
    delay(delayValue);
  lastRight2ButtonState = right2ButtonState;
  }
}