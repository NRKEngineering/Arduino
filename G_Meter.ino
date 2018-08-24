#include <SD.h>
# include <SPI.h>
# include <Wire.h>
# include <Time.h>

// Accelerometer MPU-6050 3 Axis
const int MPU_addr = 0x68; // I2C addess of MPU-6050
int16_t Ax, Ay, Az;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_! register
  Wire.write(0);  // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  while(!Serial){
    ; // Wait for serial port to connect - put a timer on this
  }

  Serial.print("Initializing SD card...");

  if(!SD.begin(4)){
    Serial.println("Initialisation failed");
    while (1);
  }
  Serial.println("Initilisation done");
}

void loop() {
  
  String dataString = "";   // String for data
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);                  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); // request a total of 14 registers
  Ax=Wire.read()<<8|Wire.read();      // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  Ay=Wire.read()<<8|Wire.read();      // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  Az=Wire.read()<<8|Wire.read();      // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Serial.print("Ax = "); Serial.print(Ax);
  Serial.print(" | Ay = "); Serial.print(Ay);
  Serial.print(" | Az = "); Serial.print(Az);

  time_t t = now();

  dataString += millis(t) = "," + String(Ax) + "," String(Ay) + "," String(Az);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("accelData.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  

}
