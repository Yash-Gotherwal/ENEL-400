/*Final code for Hexapod robot
Yash Gotherwal
200420786

This is the final code for the hexapod robot for my final capstone project.

Several changes were made from the initial commit
The final commit includes cleaning up code and adding documentation and comments
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>
#include "Servo.h"

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  //Initialize servodriver for left side legs with address (0x40)
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41); //Initialize servodriver for right side legs with address (0x41)
#define SERVOMIN  140 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  620 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

// our servo # counter
const int servoCountLeft = 9;
const int servoPinsLeft[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; //Array to store left side servos
const int servoCountRight = 9;
const int servoPinsRight[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};  //Array to store right side servos

/*left legs servo orientation
6 7 8 - leg 3 (Tibia,Femur,Coxa) /\_
3 4 5 - leg 2 (Tibia,Femur,Coxa) /\_
0 1 2 - leg 1 (Tibia,Femur,Coxa) /\_
*/
int defaultPositionsLeft[servoCountLeft] = {80, 120, 90, 100, 130, 80, 110, 150, 120};  //Default servo positions for left legs
int servoAnglesLeft[servoCountLeft];
/*Right legs servo orientation
2 1 0 - leg 4 (Coxa,Femur,Tibia) _/\
5 4 3 - leg 5 (Coxa,Femur,Tibia) _/\
8 7 6 - leg 6 (Coxa,Femur,Tibia) _/\
*/
int defaultPositionsRight[servoCountRight] = {100, 80, 50, 160, 90, 50, 160, 90, 50};   //Default servo positions for right legs
int servoAnglesRight[servoCountRight];



void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  Dabble.begin(9600);

  pwm.begin();  //begin serial communication
  pwm1.begin();
 
  pwm.setOscillatorFrequency(25000000);
  pwm.setPWMFreq(SERVO_FREQ);  
  pwm1.setOscillatorFrequency(25000000);
  pwm1.setPWMFreq(SERVO_FREQ);
  setDefaultPositions();
}

void loop() {
   Dabble.processInput();             //this function is used to refresh data obtained from smartphone.
  
  if (GamePad.isUpPressed())  // Wave function
  {
    moveServoLeft(1,50);
    moveServoLeft(0,180);
    for(int i = 0; i < 3; i++)
    {
      moveServoLeft(2,60);
      moveServoLeft(2,120);
    }
  }
  if (GamePad.isDownPressed())  //move leg 3 and leg 6 Femur up
  {
    moveServoRight(7,140); 
    moveServoLeft(7,80);
  }

  if (GamePad.isLeftPressed())  //move leg 1 and leg 4 Femur up
  {
    moveServoLeft(1,100);
    moveServoRight(1,130);
  }
   if (GamePad.isRightPressed())  //move leg 2 and leg 5 Femur up
  {
    moveServoRight(4,160);
    moveServoLeft(4,100); 
  }
  if (GamePad.isSquarePressed())  //Bow 
  {
    moveServoLeft(0,130);
    moveServoLeft(1,90);
    moveServoRight(7,140);
    moveServoRight(6,40);
  }

  if (GamePad.isCirclePressed()) // Quadruped gait function
  {
    QuadrupedGait();
  }

  if (GamePad.isCrossPressed()) //Wave gait function 
  {
    WaveGait();
  }

  if (GamePad.isTrianglePressed()) //Tripod gait function
  {
    TripodGait();
  }

  if (GamePad.isStartPressed()) // set left servos to default position
  {
    setDefaultPositionsLeft();
  }

  if (GamePad.isSelectPressed()) // set right servos to default position
  {
    setDefaultPositionsRight();
  }
}

void moveServoLeft(int servoIndex, int targetAngle) //Function to move left side servos depending on their index numbers
{
  // Smoothly move the servo to the target angle
  for (int i = servoAnglesLeft[servoIndex]; i != targetAngle; i += (targetAngle > i) ? 1 : -1)
  {
    servoAnglesLeft[servoIndex] = i;
    pwm.setPWM(servoPinsLeft[servoIndex], 0, angleToPulse(i));
    delay(10); // Adjust the delay for smoother motion
  }
}

void moveServoRight(int servoIndex, int targetAngle) //Function to move right side servos depending on their index numbers
{
//   // Smoothly move the servo to the target angle
  for (int i = servoAnglesRight[servoIndex]; i != targetAngle; i += (targetAngle > i) ? 1 : -1)
  {
  servoAnglesRight[servoIndex] = i;
  pwm1.setPWM(servoPinsRight[servoIndex], 0, angleToPulse(i));
  delay(10); // Adjust the delay for smoother motion
  }
}


void setDefaultPositions() //Set all servos to default position--> runs once at the beginning of code
{
  // Set all servos to their default positions
  for (int i = 0; i < servoCountLeft; i++)
  {
    moveServoLeft(i, defaultPositionsLeft[i]);
  }
  delay(10);
  for (int i = 0; i < servoCountRight; i++)
  {
    moveServoRight(i, defaultPositionsRight[i]);
  }
}
void setDefaultPositionsLeft() //Returns all left servos to default position
{
    for (int i = 0; i < servoCountLeft; i++)
  {
    moveServoLeft(i, defaultPositionsLeft[i]);
  }
  delay(10);
}

void setDefaultPositionsRight() //Returns all right servos to default positions
{
  for (int i = 0; i < servoCountRight; i++)
  {
    moveServoRight(i, defaultPositionsRight[i]);
  }
  delay(10);
}

int angleToPulse(int angle) //Inbuilt library function to map frequency to 0-180°
{
  // Convert angle to servo pulse length
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void moveleg1() //Servo coordinated function to move leg 1 
{
  moveServoLeft(0,130);
  delay(150);
  moveServoLeft(1,90);
  delay(150);
  moveServoLeft(2,30);
  delay(150);
  moveServoLeft(1,125);
  delay(150);
  moveServoLeft(0,80);
  delay(150);
  moveServoLeft(2,110);
  delay(150);
}

void moveleg2() //Servo coordinated function to move leg 2
{
  moveServoLeft(3,150);
  delay(150);
  moveServoLeft(4,90);
  delay(150);
  moveServoLeft(5,30);
  delay(150);
  moveServoLeft(4,140);
  delay(150);
  moveServoLeft(3,105);
  delay(150);
  moveServoLeft(5,130);
}

void moveleg3() //Servo coordinated function to move leg 3
{
  moveServoLeft(6,150);
  delay(150);
  moveServoLeft(7,110);
  delay(150);
  moveServoLeft(8,60);
  delay(150);
  moveServoLeft(7,155);
  delay(150);
  moveServoLeft(6,110);
  delay(150);
  moveServoLeft(8,150);
}

void moveleg4() //Servo coordinated function to move leg 4
{
  moveServoRight(1,120);
  delay(150);
  moveServoRight(0,40);
  delay(150);
  moveServoRight(2,70);
  delay(150);
  moveServoRight(1,70);
  delay(150);
  moveServoRight(0,110);
  delay(150);
  moveServoRight(2,30);
}

void moveleg5() //Servo coordinated function to move leg 5
{
  moveServoRight(4,100);
  delay(150);
  moveServoRight(3,40);
  delay(150);
  moveServoRight(5,90);
  delay(150);
  moveServoRight(4,80);
  delay(150);
  moveServoRight(3,160);
  delay(150);
  moveServoRight(5,20);
}

void moveleg6() //Servo coordinated function to move leg 6
{
  moveServoRight(7,120);
  delay(150);
  moveServoRight(6,40);
  delay(150);
  moveServoRight(8,120);
  delay(150);
  moveServoRight(7,70);
  delay(150);
  moveServoRight(6,150);
  delay(150);
  moveServoRight(8,50);
}

void TripodGait() //Loops leg movement in tripod gait 2 times
{
  for(int i = 0;i < 2; i++)
  {
  moveleg1();
  moveleg3();
  moveleg5();
  moveleg2();
  moveleg4();
  moveleg6();
  setDefaultPositions();
  }
}

void QuadrupedGait() //Loops leg movement in Quadruped gait 2 times
{
   for(int i = 0;i < 2; i++)
  {
  moveleg1();
  moveleg4();
  moveleg5();
  moveleg3();
  moveleg6();
  moveleg2();
  setDefaultPositions();
  }
}

void WaveGait() //Loops leg movement in wave gait 2 times
{
  for(int i = 0; i < 2;i++)
  {
    moveleg4();
    moveleg5();
    moveleg6();
    setDefaultPositionsRight();
    moveleg3();
    moveleg2();
    moveleg1();
    setDefaultPositionsLeft();
  }
}