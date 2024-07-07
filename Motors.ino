#include "Motors.h"
#include "OledAndIR.h"

const int baseSpeed = 75;
const int highSpeed = 140;
const int lowSpeed = 70;

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

  // Read sensors
  int leftMost = analogRead(irSensor1);
  int left = analogRead(irSensor2);
  int center = analogRead(irSensor3);
  int right = analogRead(irSensor4);
  int rightMost = analogRead(irSensor5);

  // Line following logic
  if (center > thresholds[2]) {
    // Move forward if the center sensor is on the line
    adjustSpeed(baseSpeed, baseSpeed);
    forward();
  } else if (left > thresholds[1] && center <= thresholds[2]) {
    // Turn slightly left if the left sensor is on the line and center sensor is not
    adjustSpeed(lowSpeed, baseSpeed);
    turnLeft();
  } else if (right > thresholds[3] && center <= thresholds[2]) {
    // Turn slightly right if the right sensor is on the line and center sensor is not
    adjustSpeed(baseSpeed, lowSpeed);
    turnRight();
  } else if (leftMost > thresholds[0] && left <= thresholds[1]) {
    // Sharp left turn if the leftmost sensor is on the line and left sensor is not
    adjustSpeed(lowSpeed, highSpeed);
    turnLeft();
  } else if (rightMost > thresholds[4] && right <= thresholds[3]) {
    // Sharp right turn if the rightmost sensor is on the line and right sensor is not
    adjustSpeed(highSpeed, lowSpeed);
    turnRight();
  } else if (leftMost <= thresholds[0] && left <= thresholds[1] && center <= thresholds[2] && right <= thresholds[3] && rightMost <= thresholds[4]) {
    // If all sensors detect white, turn back
    adjustSpeed(lowSpeed, lowSpeed);
    turnBack();
    while (center <= thresholds[2]) {
      // Keep turning back until the center sensor detects the line
      turnBack();
    }
    forward();
  } else if (leftMost > thresholds[0] && left > thresholds[1] && center > thresholds[2] && right > thresholds[3] && rightMost > thresholds[4]) {
    // If all sensors detect black, the robot is at an intersection
    adjustSpeed(baseSpeed, baseSpeed);
    turnRight(); // Prioritize turning right at the intersection
  }
}
