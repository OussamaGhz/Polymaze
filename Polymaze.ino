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
int baseSpeed = 100;

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
  // Read sensor values and determine if over black or white
  int leftSensor = analogRead(irSensor2) > calibratedThresholds[0] ? 1 : 0;
  int middleSensor = analogRead(irSensor3) > calibratedThresholds[1] ? 1 : 0;
  int rightSensor = analogRead(irSensor4) > calibratedThresholds[2] ? 1 : 0;

  // Calculate error based on sensor values
  error = leftSensor - rightSensor;

  // PID calculations
  integral += error;
  derivative = error - previousError;
  float correction = Kp * error + Ki * integral + Kd * derivative;

  // Adjust motor speeds based on correction
  int speedA = baseSpeed + correction;
  int speedB = baseSpeed - correction;

  // Ensure the speeds are within valid range
  speedA = constrain(speedA, 0, 255);
  speedB = constrain(speedB, 0, 255);

  // Move forward with adjusted speeds
  forward();
  adjustSpeed(speedA, speedB);

  // Update previous error
  previousError = error;
}
