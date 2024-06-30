#include "MotorsAndBuzzer.h"
#include "OledAndIR.h"

void initializeMotorsAndBuzzer() {
  pinMode(enb, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(en3, OUTPUT);
  pinMode(en4, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void controlMotorsAndBuzzer(int sensorValues[]) {
  bool obstacleDetected = false;
  for (int i = 0; i < 5; i++) {
   if (sensorValues[i] >= thresholds[i]) {
      obstacleDetected = true;
      break;
    }
  }

  if (obstacleDetected) {
    digitalWrite(led, HIGH);
    // digitalWrite(buzzer, HIGH);
    digitalWrite(enb, HIGH);
    digitalWrite(en1, HIGH);
    digitalWrite(en2, LOW);
    digitalWrite(en3, HIGH);
    digitalWrite(en4, LOW);
  } else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(enb, LOW);
    digitalWrite(en1, LOW);
    digitalWrite(en2, LOW);
    digitalWrite(en3, LOW);
    digitalWrite(en4, LOW);
  }
}