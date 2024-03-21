
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

// our servo # counter
const int servoCount = 3;
const int servoPins[] = {0, 1, 2};

int defaultPositions[servoCount] = {90, 90, 90};
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
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    moveServo(0,140);
    Serial.print("UP");
  }

  if (GamePad.isDownPressed())
  {
    moveServo(1,150);
    Serial.print("DOWN");
  }

  if (GamePad.isLeftPressed())
  {
    moveServo(2,140);
    moveServo(1,170);
    moveServo(0,150);
    moveServo(2,90);
    moveServo(1,90);
    moveServo(0,90);

    

    Serial.print("Left");
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
