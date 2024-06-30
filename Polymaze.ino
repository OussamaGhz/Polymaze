#include "OledAndIR.h"
#include "MotorsAndBuzzer.h"

void setup() {
  initializeDisplayAndSensors();
  initializeMotorsAndBuzzer();
}

void loop() {
  runOnce();
  delay(300); // Adjust the delay as needed for your application
}
