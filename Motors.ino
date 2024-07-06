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

  // Line following logic
  if (analogRead(irSensor2) < thresholds[1] && analogRead(irSensor3) > thresholds[2] && analogRead(irSensor4) < thresholds[3]) {
    // Move forward
    adjustSpeed(baseSpeed, baseSpeed);
    forward();
  } if (analogRead(irSensor2) > thresholds[1]&& analogRead(irSensor3) < thresholds[2]) {
   while (analogRead(irSensor3) < thresholds[2]) {
   adjustSpeed(baseSpeed, lowSpeed);
   }
   adjustSpeed(baseSpeed, baseSpeed);
  }  if (analogRead(irSensor4) > thresholds[3] && analogRead(irSensor3)< thresholds[2]) {
    while (analogRead(irSensor3) < thresholds[2]) {
   adjustSpeed(lowSpeed, baseSpeed);
   }
   adjustSpeed(baseSpeed, baseSpeed);
  }  if ((analogRead(irSensor1) < thresholds[0] && analogRead(irSensor2) < thresholds[1] && analogRead(irSensor3) < thresholds[2] && analogRead(irSensor4) < thresholds[3] && analogRead(irSensor5) < thresholds[4])) {
    turnBack();
     while (analogRead(irSensor3) < thresholds[2]) {
   turnBack();
   adjustSpeed(lowSpeed, lowSpeed);
   }
   adjustSpeed(baseSpeed, baseSpeed);
   forward();
  }
}