#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <dht.h>


dht DHT;
#define DHT11_PIN 28
// Adafruit_BMP280 bmp280; // tworzymy odnośnik do biblioteki

// //bool setSDA(pin_size_t sda);
// //bool setSCL(pin_size_t scl);

// const int mpu_addr=0x68; 
// bool setSDA(pin_size_t sda);
// bool setSCL(pin_size_t scl);
void setup() {
  // Wire.begin();
  // Wire.setClock(400000L); // Set I2C frequency to 400kHz
  // Wire.beginTransmission(mpu_addr);
  // Wire.write(0x6B);
  // Wire.write(0); // wake up the mpu6050
  // Wire.endTransmission(true);
  Serial.begin(9600);
  //pinMode(28, INPUT);
  // Serial.println("Arduino + BMP280");
  
  // if (!bmp280.begin(0x76)) //w nawiasie podajemy nasz adres I2C tutaj wpisałem 0x76
  // {  // sprawdzamy czy czujnik odpowiada jesli nie wyświetlamy komunikat o błędzie
  //   Serial.println("Nie znaleziono czujnika - sprawdź połączenie!");
  //   while (1);
  // }

}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.println(DHT.temperature);
  // odczytujemy temperaturę, ciśnienie i wysokość
  // float temperature = bmp280.readTemperature(); 
  // float pressure    = bmp280.readPressure();    
  // float altitude_   = bmp280.readAltitude(1013.25);

  
  // // Wypisujemy wyniki pomiarów
  // // 1:  temperatura
  // Serial.print("Temperatura = ");
  // Serial.print(temperature);
  // Serial.println("°C");
  // // 2:  ciśnienie
  // Serial.print("Ciśnienie    = ");
  // Serial.print(pressure/100);
  // Serial.println("hPa");
  // // 3:  wysokość
  // Serial.print("Wysokość = ");
  // Serial.print(altitude_);
  // Serial.println("m");
    
  // Serial.println();  // nowa linie
  // delay(2000);       // czekamy 2 sekundy
  
}
// koniec programu, wykonuje się w pętli od nowa