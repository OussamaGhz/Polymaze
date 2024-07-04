#include "OledAndIR.h"
#include "Motors.h"

void setup() {
  initializeDisplayAndSensors();
  initializeMotors();
  //calibrateRobot(); // Call the calibration function
}

void loop() {
  //runOnce();

adjustSpeed(50,50);
turnBack();

}
