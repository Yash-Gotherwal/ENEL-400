
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>
#include "Servo.h"

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
#define SERVOMIN  140 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  620 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

// our servo # counter
const int servoCountLeft = 9;
const int servoPinsLeft[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const int servoCountRight = 9;
const int servoPinsRight[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};


int defaultPositionsLeft[servoCountLeft] = {80, 120, 90, 100, 130, 80, 110, 150, 120};
int servoAnglesLeft[servoCountLeft];
int defaultPositionsRight[servoCountRight] = {100, 80, 50, 160, 90, 50, 160, 90, 50};
int servoAnglesRight[servoCountRight];



void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  Dabble.begin(9600);

  pwm.begin();
  pwm1.begin();
 
  pwm.setOscillatorFrequency(25000000);
  pwm.setPWMFreq(SERVO_FREQ);  
  pwm1.setOscillatorFrequency(25000000);
  pwm1.setPWMFreq(SERVO_FREQ);
  setDefaultPositions();
}

void loop() {
   Dabble.processInput();             //this function is used to refresh data obtained from smartphone.
  
  if (GamePad.isUpPressed())
  {
    moveServoLeft(1,50);
    moveServoLeft(0,180);
    for(int i = 0; i < 3; i++)
    {
      moveServoLeft(2,60);
      moveServoLeft(2,120);
    }
    Serial.print("UP");
  }
  if (GamePad.isDownPressed())
  {
    moveServoRight(7,140); 
    moveServoLeft(7,80);
  }

  if (GamePad.isLeftPressed())  //initial movement for left side
  {
   moveServoLeft(1,100);
   moveServoRight(1,130);
  }
   if (GamePad.isRightPressed())
  {
   
   moveServoRight(4,160);
   moveServoLeft(4,100); 
   Serial.print("Right");
  }
  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    QuadrupedGait();
    Serial.print("Circle");
  }

  if (GamePad.isCrossPressed())
  {
    RippleGait();
    Serial.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    TripodGait();
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    setDefaultPositionsLeft();
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    setDefaultPositionsRight();
    Serial.print("Select");
  }
}

void moveServoLeft(int servoIndex, int targetAngle)
{
  // Smoothly move the servo to the target angle
  for (int i = servoAnglesLeft[servoIndex]; i != targetAngle; i += (targetAngle > i) ? 1 : -1)
  {
    servoAnglesLeft[servoIndex] = i;
    pwm.setPWM(servoPinsLeft[servoIndex], 0, angleToPulse(i));
    delay(10); // Adjust the delay for smoother motion
  }
}

void moveServoRight(int servoIndex, int targetAngle)
{
//   // Smoothly move the servo to the target angle
  for (int i = servoAnglesRight[servoIndex]; i != targetAngle; i += (targetAngle > i) ? 1 : -1)
  {
  servoAnglesRight[servoIndex] = i;
  pwm1.setPWM(servoPinsRight[servoIndex], 0, angleToPulse(i));
  delay(10); // Adjust the delay for smoother motion
  }
}


void setDefaultPositions()
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
void setDefaultPositionsLeft()
{
    for (int i = 0; i < servoCountLeft; i++)
  {
    moveServoLeft(i, defaultPositionsLeft[i]);
  }
  delay(10);
}

void setDefaultPositionsRight()
{
  for (int i = 0; i < servoCountRight; i++)
  {
    moveServoRight(i, defaultPositionsRight[i]);
  }
  delay(10);
}

int angleToPulse(int angle)
{
  // Convert angle to servo pulse length
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void moveleg1()
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

void moveleg2()
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

void moveleg3()
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

void moveleg4()
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

void moveleg5()
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

void moveleg6()
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

void TripodGait()
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

void QuadrupedGait()
{
   for(int i = 0;i < 2; i++)
  {
  moveleg1();
  moveleg4();
  moveleg5();
  moveleg3();
  moveleg6();
  moveleg2();
  }
}

void RippleGait()
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