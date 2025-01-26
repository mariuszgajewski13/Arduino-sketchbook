#include<Wire.h>

const int mpu_addr=0x68; 

float accX, accY, accZ, temp, gyX, gyY, gyZ;
float dt0;
unsigned long time_i, time_f, time_d; 
float aX_a, aY_a, angleX, angleY, angleY_prev, angleY_sum;
float filter_r = 0.94;
float accX_0, accY_0, accZ_0, gyX_0, gyY_0, gyZ_0;


bool setSDA(pin_size_t sda);
bool setSCL(pin_size_t scl);

void setup(){
  Wire.begin();
  Wire.setClock(400000L); // Set I2C frequency to 400kHz
  Wire.beginTransmission(mpu_addr);
  Wire.write(0x6B);
  Wire.write(0); // wake up the mpu6050
  Wire.endTransmission(true);
  //Gyro config
  Wire.beginTransmission(mpu_addr);       //begin, Send the slave adress (in this case 68) 
  Wire.write(0x1B);                       //We want to write to the GYRO_CONFIG register (1B hex)
  Wire.write(0x08);                       //Set the register bits as 00001000 (500dps full scale)
                                          //00000000 - 250dps; 00001000 - 500dps; 00010000 - 1000dps; 00011000 - 2000dps
  Wire.endTransmission(true);             //End the transmission with the gyro
  //Acc config
  Wire.beginTransmission(mpu_addr);       //Start communication with the address found during search.
  Wire.write(0x1C);                       //We want to write to the ACCEL_CONFIG register
  Wire.write(0x00);                       //Set the register bits as 00000000 (+/- 2g full scale range)
                                          //00000000 - 2g; 00001000 - 4g; 00010000 - 8g; 00011000 - 16g;
  Wire.endTransmission(true); 



  for (int i = 0; i < 500; i++) 
  {
    gyroRead();
    delay(10);
  }

  accX_0 = 0;
  accY_0 = 0;
  accZ_0 = 0;
  gyX_0 = 0;
  gyY_0 = 0;
  gyZ_0 = 0;

  for (int i = 0; i < 100; i++) 
  {
    gyroRead();
    accX_0 = accX_0 + accX;
    accY_0 = accY_0 + accY;
    accZ_0 = accZ_0 + accZ;
    gyX_0 = gyX_0 + gyX;
    gyY_0 = gyY_0 + gyY;
    gyZ_0 = gyZ_0 + gyZ;
    delay(10);
  }
  accX_0 = accX_0 / 100.0;
  accY_0 = accY_0 / 100.0;
  accZ_0 = -1.0 + accZ_0 / 100.0;
  gyX_0 = gyX_0 / 100.0;
  gyY_0 = gyY_0 / 100.0;
  gyZ_0 = gyZ_0 / 100.0;

  angleX = 0;
  angleY = 0;
  
  time_f = micros();

  angleY = 0;
  angleY_prev = 0;
  angleY_sum = 0;

}
void loop(){
  gyroRead();
  accX = accX - accX_0;
  accY = accY - accY_0;
  accZ = accZ - accZ_0;
  gyX = gyX - gyX_0;
  gyY = gyY - gyY_0;
  gyZ = gyZ - gyZ_0;
  
  aX_a = 57.29578 * atan(accY/sqrt(accX*accX+accZ*accZ));
  aY_a = 57.29578 * atan(accX/sqrt(accY*accY+accZ*accZ));
 // aY_a = atan(accX/sqrt(accY*accY+accZ*accZ));

  time_i = time_f;
  time_f = micros();
  dt0 = float(time_f - time_i) / 1.0e6;
  angleX = filter_r * (angleX + gyX * dt0) + (1 - filter_r) * aX_a; 
  angleY = filter_r * (angleY + gyY * dt0) + (1 - filter_r) * aY_a; 
//  Serial.println(angleY);

  angleY_prev = angleY;
  angleY_sum += angleY;
  
  // Serial.print("Accelerometer: ");
  // Serial.print("X = "); Serial.print(accX);
  // Serial.print(" | Y = "); Serial.print(accY);
  // Serial.print(" | Z = "); Serial.println(accZ); 
  
  // Serial.print("Gyroscope: ");
  // Serial.print("X = "); Serial.print(gyX);
  // Serial.print(" | Y = "); Serial.print(gyY);
  // Serial.print(" | Z = "); Serial.println(gyZ);
  // Serial.println(" ");

  Serial.print("X: ");
  Serial.print(angleX);
  Serial.print("   |   ");
  Serial.print("Y: ");
  Serial.print(angleY);
  Serial.println();

  //delay(10);

  time_d = micros();
  while (micros() - time_d < 6000) {}
}

void gyroRead() {
  // reading gyroscope parameters
  Wire.beginTransmission(mpu_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(mpu_addr, 14, true);
//  accX = float(Wire.read()<<8|Wire.read())/16384.0;  // 16384 - 2g; 8192 - 4g; 4096 - 8g; 2048 - 16g
//  accY = float(Wire.read()<<8|Wire.read())/16384.0;
//  accZ = float(Wire.read()<<8|Wire.read())/16384.0;
  accX = 6.1035e-5 * float(Wire.read()<<8|Wire.read());  // 16384 - 2g; 8192 - 4g; 4096 - 8g; 2048 - 16g
  accY = 6.1035e-5 * float(Wire.read()<<8|Wire.read());
  accZ = 6.1035e-5 * float(Wire.read()<<8|Wire.read());
  temp = Wire.read()<<8|Wire.read();
//  gyX = float(Wire.read()<<8|Wire.read())/65.536; // 131072 - 250deg/s; 65536 - 500deg/s; 32768 - 1000deg/s; 16384 - 2000deg/s
//  gyY = float(Wire.read()<<8|Wire.read())/65.536; // dodatkowo rad2deg * 57.29578
//  gyZ = float(Wire.read()<<8|Wire.read())/65.536;
  gyX = 2.6632e-4 * float(Wire.read()<<8|Wire.read()); // 131072 - 250deg/s; 65536 - 500deg/s; 32768 - 1000deg/s; 16384 - 2000deg/s
  gyY = 2.6632e-4 * float(Wire.read()<<8|Wire.read()); // dodatkowo rad2deg * 57.29578
  gyZ = 2.6632e-4 * float(Wire.read()<<8|Wire.read());
  Wire.endTransmission(true);
 // Serial.println(gyY);
}

