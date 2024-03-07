#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Servo.h>
#include <Dabble.h>

Servo coxa;
Servo femur;
Servo tibia;
void setup() {
 // put your setup code here, to run once:
  coxa.attach(7);
  femur.attach(8);
  tibia.attach(9);
  Serial.begin(9600);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.println("UP");
    coxa.write(90);
    femur.write(90);
    tibia.write(90);
  }

  else if (GamePad.isDownPressed())
  {
    Serial.println("DOWN");
    coxa.write(100);
    femur.write(100);
    tibia.write(100);
  }

  else if (GamePad.isLeftPressed())
  {
    Serial.println("Left");
    coxa.write(110);
    femur.write(110);
    tibia.write(110);
  }

  else if (GamePad.isRightPressed())
  {
    Serial.println("Right");
    coxa.write(120);
    femur.write(120);
    tibia.write(120);
  }
}
