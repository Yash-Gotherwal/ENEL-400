#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.println("UP");
  }

  else if (GamePad.isDownPressed())
  {
    Serial.println("DOWN");
  }

  else if (GamePad.isLeftPressed())
  {
    Serial.println("Left");
  }

  else if (GamePad.isRightPressed())
  {
    Serial.println("Right");
  }
}
