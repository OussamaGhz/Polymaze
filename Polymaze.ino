#include "OledAndIR.h"
#include "Motors.h"

// PID constants
const float Kp = 1.0;
const float Ki = 0.0;
const float Kd = 0.0;

// Variables for PID
float error = 0.0;
float previousError = 0.0;
float integral = 0.0;
float derivative = 0.0;


// Global variable for thresholds
int calibratedThresholds[3];

void setup() {
  Serial.begin(9600);
  initializeDisplayAndSensors();
  initializeMotors();
  // Call the calibration function and store the thresholds
  int* thresholds = calibrateRobot();
  calibratedThresholds[0] = thresholds[0];
  calibratedThresholds[1] = thresholds[1];
  calibratedThresholds[2] = thresholds[2];
}

void loop() {
  runOnce();
  controlMotorsAndBuzzer(lastSensorValues);
}
