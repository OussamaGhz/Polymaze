#include "Motors.h"
#include "OledAndIR.h"

const int baseSpeed = 100;
const int highSpeed = 150;
const int lowSpeed = 50;

void initializeMotors() {
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(led, OUTPUT);
}

void adjustSpeed(int speedA, int speedB) {
  analogWrite(ena, speedA);
  analogWrite(enb, speedB);
}

void backward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void turnBack() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void controlMotorsAndBuzzer(int sensorValues[]) {
  // Print sensor values for debugging
  for (int i = 0; i < 5; i++) {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Line following logic
  if (sensorValues[1] < thresholds[1] && sensorValues[2] > thresholds[2] && sensorValues[3] < thresholds[3]) {
    // Move forward
    adjustSpeed(baseSpeed, baseSpeed);
    forward();
  } else if (sensorValues[1] > thresholds[1] || sensorValues[0] > thresholds[0]) {
    // Turn slightly left
    adjustSpeed(highSpeed, lowSpeed);
    forward();
  } else if (sensorValues[3] > thresholds[3] || sensorValues[4] > thresholds[4]) {
    // Turn slightly right
    adjustSpeed(lowSpeed, highSpeed);
    forward();
  } else if ((sensorValues[0] < thresholds[0] && sensorValues[1] < thresholds[1] && sensorValues[2] < thresholds[2] && sensorValues[3] < thresholds[3] && sensorValues[4] < thresholds[4]) || (sensorValues[0] > thresholds[0] && sensorValues[1] > thresholds[1] && sensorValues[2] > thresholds[2] && sensorValues[3] > thresholds[3] && sensorValues[4] > thresholds[4])) {
    // Stop if all sensors detect either all black or all white
    adjustSpeed(0, 0);
  }
}