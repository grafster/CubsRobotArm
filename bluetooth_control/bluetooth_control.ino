
#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
String inString = "";    // string to hold input

void setup() {
  // Servos attached on pins 9 - 11
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {
  // Read serial input:

  while (Serial.available() > 0) {
    int inChar = Serial.read();
    inString += (char)inChar;

    // if you get a newline, process the string - should be in the form s1-90:
    if (inChar == '\n') {
      int servoNumber = -1;
      if (inString[0] == 's' && inString[2] == '-'){
        // Convert from an ascii character to an integer
        servoNumber = inString[1] -'0'; 

        String angleString;
        int z = 3;
        // process the input string up to the decimal point (or the end of the string)
        while (z < inString.length() && inString[z] != '.'){
          angleString += inString[z];
          z++;
     
        }

        if (servoNumber == 1)
          myservo1.write(angleString.toInt());
        else if (servoNumber == 2)
          myservo2.write(angleString.toInt());
        else if (servoNumber == 3)
          myservo3.write(angleString.toInt());
      }
      else if (inString[0] == 'p'){
        delay(1000);
      }

      inString = "";
    }
  }
}
