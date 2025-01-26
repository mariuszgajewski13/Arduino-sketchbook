// Definicja pinów sterujących silnikiem
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

// Definicja pinów przycisków
const int buttonCW = 5;  // Przycisk do obrotu w prawo
const int buttonCCW = 6; // Przycisk do obrotu w lewo

// Opóźnienie między krokami (im mniejsze, tym szybsze obroty)
int stepDelay = 5; // w milisekundach

int stepss = 50;

// Tablica sekwencji sterowania (4-fazowa pełnokrokowa)
int stepSequence[8][4] = {
  {1, 0, 0, 0}, // Fazowanie na IN1
  {1, 1, 0, 0}, // Fazowanie na IN1 i IN2
  {0, 1, 0, 0}, // Fazowanie na IN2
  {0, 1, 1, 0}, // Fazowanie na IN2 i IN3
  {0, 0, 1, 0}, // Fazowanie na IN3
  {0, 0, 1, 1}, // Fazowanie na IN3 i IN4
  {0, 0, 0, 1}, // Fazowanie na IN4
  {1, 0, 0, 1}  // Fazowanie na IN1 i IN4
};

// Liczba kroków w sekwencji (8 dla półkroków)
const int stepsInSequence = 8;

void setup() {
  // Konfiguracja pinów jako wyjścia
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Konfiguracja pinów przycisków jako wejścia z podciąganiem
  pinMode(buttonCW, INPUT_PULLUP);
  pinMode(buttonCCW, INPUT_PULLUP);

  // Początkowy stan wyjść
  stopMotor();

  Serial.begin(9600);
  Serial.println("Silnik krokowy gotowy!");
}

void loop() {
  // Sprawdzenie stanu przycisków
  if (digitalRead(buttonCW) == LOW) { // Przyciśnięty przycisk obrotu w prawo
    Serial.println("Obrót w prawo");
    rotateMotor(stepss, true); // Obrót o 50 kroków w prawo
  }

  if (digitalRead(buttonCCW) == LOW) { // Przyciśnięty przycisk obrotu w lewo
    Serial.println("Obrót w lewo");
    rotateMotor(stepss, false); // Obrót o 50 kroków w lewo
  }
}

// Funkcja sterująca ruchem silnika
void rotateMotor(int steps, bool clockwise) {
  for (int i = 0; i < steps; i++) {
    // Wyliczenie indeksu sekwencji
    int stepIndex = (clockwise) ? i % stepsInSequence : (stepsInSequence - (i % stepsInSequence) - 1);
    
    // Ustawienie stanów na pinach
    setMotorPins(stepSequence[stepIndex]);
    delay(stepDelay);
  }

  // Wyłączenie silnika po zakończeniu
  stopMotor();
}

// Funkcja ustawiająca piny sterujące
void setMotorPins(int stepState[4]) {
  digitalWrite(IN1, stepState[0]);
  digitalWrite(IN2, stepState[1]);
  digitalWrite(IN3, stepState[2]);
  digitalWrite(IN4, stepState[3]);
}

// Funkcja zatrzymująca silnik
void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
