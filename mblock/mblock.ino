
#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
int servo1Angle = 90;
int servo2Angle = 90;
int servo3Angle = 90; 
int servo4Angle = 90;
int delayTime = 10;

void setup() {
  // Servos attached on pins 8 - 11
  myservo1.attach(8);
  myservo2.attach(9);
  myservo3.attach(10);
  myservo4.attach(11);
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Awaiting input");
  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
  delay(500);  
  myservo1.write(120);
  myservo2.write(120);
  myservo3.write(120);
  myservo4.write(120);
  delay(500);  
  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
  delay(500);  
}

void moveServoToAngle(Servo& servo, int& currentAngle, const int targetAngle)
{
  Serial.print("Moving to angle ");
  Serial.print (targetAngle);
  Serial.print (" current angle = ");
  Serial.print(currentAngle);
  Serial.print (" target angle = ");
  Serial.println(targetAngle);
  if (currentAngle < targetAngle)
  {
    while (currentAngle < targetAngle)
    {
      currentAngle++;
    
      servo.write(currentAngle);
      delay(delayTime);
    }
  }
  else 
  {
    while (currentAngle > targetAngle)
    {
      currentAngle--;
    
      servo.write(currentAngle);
      delay(delayTime);
    }
  
  }
  Serial.println("Move Complete");
  
}
void loop() {
  // Read serial input:

  while (Serial.available() > 0) {
    int servoNumber = Serial.read();
    int angle = Serial.read();

    Serial.print("ServoNum = "); Serial.print(servoNumber);
    Serial.print(" angle = "); Serial.println(angle);
    
    // if you get a newline, process the string - should be in the form s1-90:

        if (servoNumber == 1)
        {
          moveServoToAngle(myservo1, servo1Angle, angle);         
        }
        else if (servoNumber == 2)
        {
          moveServoToAngle(myservo2, servo2Angle, angle);         
        }
        else if (servoNumber == 3)
        {
          moveServoToAngle(myservo3, servo3Angle, angle);         
        }
        else if (servoNumber == 4)
        {
          moveServoToAngle(myservo4, servo4Angle, angle);         
        }
      }
    
}
