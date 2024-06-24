#include "OledAndIR.h"

void setup() {
  initializeDisplayAndSensors();
}

void loop() {
  runOnce();
  delay(300); // Adjust the delay as needed for your application
}
