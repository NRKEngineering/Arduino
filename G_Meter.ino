#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <TimeLib.h>
#include <math.h>

// Accelerometer MPU-6050 3 Axis

/* How to connect GY-521
  VCC - 5v
  GND - GND
  SCL - A5
  SDA - A4
*/

const int MPU_addr = 0x68; // I2C addess of MPU-6050
int16_t Ax, Ay, Az,Tmp,GyX,GyY,GyZ, ARes, GVal;
string filename;
time t;

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
    return;
  }
  Serial.println("Initilisation done");
  
  // Create file to write too
  t = now();                        // Get current time and date
  filename = String(String(day(t)) + String(month(t))+ String(year(t))+ "_" + String(hour(t)) + String(minute(t)) + "_data.csv");
  //filename = "28082018_0000_data.csv";
  Serial.print(" Filename is " + filename);
  File dataFile = SD.open(filename, FILE_WRITE);
  dataFile.println("Time, Acceleration,G-Force");
  dataFile.close();
  
}

void loop() {
  
  // String dataString = "";   // String for data
  
  Wire.beginTransmission(MPU_addr);   // Start talking to accelerometer
  Wire.write(0x3B);                   // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);        // Send restart message to keep connection alive
  Wire.requestFrom(MPU_addr,6,true); // request a total of 14 registers
  t = now();                   // Get milliseconds since device start for time stamp
  Ax=Wire.read()<<8|Wire.read();      // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  Ay=Wire.read()<<8|Wire.read();      // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  Az=Wire.read()<<8|Wire.read();      // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
  ARes = sqrt(pow(Ax,2)+pow(Ay,2)+pow(Az,2)); // calculate resultant of acceleratons
  
  GVal = (ARes*0.061) - 1000;         // Convert raw data to G-Force
  
  // Optional print to serial 
  //Serial.print("Accelerometer: ");
  //Serial.print("Ax = "); Serial.print(Ax);
  //Serial.print(" | Ay = "); Serial.print(Ay);
  //Serial.print(" | Az = "); Serial.print(Az);
 
  // This prints: time, raw G Value, coverted G Value
  //Serial.print(String(millis()));
  //Serial.print(","); Serial.print(ARes);
  //Serial.print(","); Serial.print(GVal);
  string dataString = String(String(millis()) + "," + String(ARes) + "," + String(GVal));
	
	
	// print to serial
	Serial.println(dataString);
  Serial.println(" ");
  
	
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open(filename, FILE_WRITE);

	
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
