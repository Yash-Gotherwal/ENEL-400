
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

// our servo # counter
const int servoCount = 9;
const int servoPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
//const int servoCountright = 9;
//const int servoPinsRight[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

int defaultPositions[servoCount] = {50, 0, 90, 75, 130, 70, 75, 0, 130};
int servoAngles[servoCount];

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  Dabble.begin(9600);

  pwm.begin();
 
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  
  for (int i = 0; i < servoCount; i++)
  {
    servoAngles[i] = defaultPositions[i];
    pwm.setPWM(servoPins[i], 0, angleToPulse(servoAngles[i]));
  }
  delay(10);
}

void loop() {
   Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  
  if (GamePad.isUpPressed())
  {
    moveServo(0,90);
    delay(1000);
    moveServo(1,10);
    delay(1000);
    moveServo(2,120);
    delay(1000);
    moveServo(3,90);
    delay(1000);
    moveServo(4,90);
    delay(1000);
    moveServo(5,90);
    delay(1000);
    moveServo(6,90);
    delay(1000);
    moveServo(7,10);
    delay(1000);
    moveServo(8,90);
    delay(1000);
    Serial.print("UP");
  }

  if (GamePad.isDownPressed())
  {
     for (int i = 0; i < servoCount; i++)
  {
    servoAngles[i] = defaultPositions[i];
    pwm.setPWM(servoPins[i], 0, angleToPulse(servoAngles[i]));
  }
  delay(10);
  }

  if (GamePad.isLeftPressed())  //initial movement for left side
  {
    moveServo(0,130);
    delay(1000);
    moveServo(2,60);
    delay(1000);
    moveServo(0,50);
    delay(1000);
    moveServo(2,90);
    delay(1000);
    moveServo(6,130);
    delay(1000);
    moveServo(8,90);
    delay(1000);
    moveServo(6,75);
    delay(1000);
    moveServo(8,130);
    delay(1000);
    moveServo(3,60);
    delay(1000);
    moveServo(4,60);
    delay(1000);
    moveServo(5,90);
  }
   if (GamePad.isRightPressed())
  {
    moveServo(0,90);
    moveServo(1,90);
    moveServo(2,90);

    Serial.print("Right");
  }

}

void moveServo(int servoIndex, int targetAngle)
{
  // Smoothly move the servo to the target angle
  for (int i = servoAngles[servoIndex]; i != targetAngle; i += (targetAngle > i) ? 1 : -1)
  {
    servoAngles[servoIndex] = i;
    pwm.setPWM(servoPins[servoIndex], 0, angleToPulse(i));
    delay(10); // Adjust the delay for smoother motion
  }
}
void setDefaultPositions()
{
  // Set all servos to their default positions
  for (int i = 0; i < servoCount; i++)
  {
    moveServo(i, defaultPositions[i]);
  }
}

int angleToPulse(int angle)
{
  // Convert angle to servo pulse length
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}
