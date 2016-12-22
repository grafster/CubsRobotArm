#include <SPI.h>

#include <SD.h>
#include <Wire.h>


/// Logs to the file <FileName> on the SD card. Change currentSensorPort to the port that the ACS712 is connected to.

// RTC code copied from http://tronixstuff.com/2014/12/01/tutorial-using-ds1307-and-ds3231-real-time-clock-modules-with-arduino/

#define DS3231_I2C_ADDRESS 0x68

unsigned long sampleTime = 0;

const unsigned long sampleFrequency = 5 * 60 * 1000UL; // Defaulting to 5 minutes

const int currentSensorPort = A0;

const int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module

const int ACSoffset = 2500; // Not sure where this number comes from http://henrysbench.capnfatz.com/henrys-bench/arduino-current-measurements/the-acs712-current-sensor-with-an-arduino/

char* FileName = "current.csv";


// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}



void setup() {
  Wire.begin();
  Serial.begin(9600);
   
  pinMode (A0, INPUT);
  // put your setup code here, to run once:
  if (!SD.begin()){
    Serial.println("SD Begin Failed");
  }
  
  // If the log file doesn't exist, write out the column headers
  if (!SD.exists(FileName)){
    File outfile = SD.open(FileName, FILE_WRITE);
    if (outfile){
      outfile.write("Time,RawValue,MilliVolts,Amps\r\n"); // output column headers
      outfile.close();
    }
    else {
      Serial.println ("Error opening file");
    }
    
  }
  
  writeCurrentToLogFile();
}

void outputTime(File& outfile)
{
   byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  
  outfile.write(String(dayOfMonth).c_str());
  outfile.write("/");
  outfile.write(String(month).c_str());
  outfile.write("/");
  outfile.write(String(year).c_str());
  outfile.write(" ");
  outfile.write(String(hour).c_str());
  outfile.write(":");
  outfile.write(String(minute).c_str());
  outfile.write(":");
  outfile.write(String(second).c_str());
  
  
}

void writeCurrentToLogFile(){

  File outFile = SD.open(FileName, FILE_WRITE);
  
  // If opening the file worked
  if (outFile){
    outputTime(outFile);

    int rawValue = analogRead(currentSensorPort);
    double voltage = (rawValue / 1024.0) * 5000; // Gets you mV
    double amps = ((voltage - ACSoffset) / mVperAmp);
    
    outFile.write(",");
    outFile.write(String(rawValue).c_str());
    outFile.write(",");
    outFile.write(String(voltage, 6).c_str()); // Output to 6 decimal places
    outFile.write(",");
    outFile.write(String(amps, 6).c_str()); // Output to 6 decimal places
    
    outFile.write("\r\n"); // Output newline
    outFile.close();
  }
  else {
    Serial.println ("Error opening file");
  }    
}

void loop() {
  
  unsigned long now = millis();
  if (now - sampleTime >= sampleFrequency){
    sampleTime += sampleFrequency;
    writeCurrentToLogFile();
  }
  
  
  
}
