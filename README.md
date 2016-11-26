# CubsRobotArm

Connect servos to Ports 8 - 11 on the arduino.

8 = right hand servo 
9 = left hand servo
10 = base rotation servo
11 = claw servo

# Bluetooth control

Wire the bluetooth module into the DeekRobot, ensuring that RX on the DeekRobot is connected to the TX on the bluetooth module and vice versa.

Install the APK file on your android device

Flash bluetooth_control.ino to the arduino. 

Start android app and click "select device" and pick the arduino bluetooth module

Have fun playing with the sliders, or buttons depending on which apk you installed.

# mBlock control

To control the arm from mBlock:-

Install the mBlock software from http://http://www.mblock.cc/
Program the arduino with the software mblock.ino
Open the mblock software and go to Extensions -> Manage Extensions and click Add Extension. 
Add mblock_mearm_extension.zip 
The blocks for controlling the arm should appear under the robots menu. 

Note that this only works in direct control mode - i.e. when you are connected from mBlock to the arm over serial or bluetooth, and events like "When Space Key Pressed" to start the program


# Other notes

If you are using USB serial to control the aprm, disconnect the bluetooth module as it seems to interfere.


