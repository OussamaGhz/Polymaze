#ifndef OLED_AND_IR_H
#define OLED_AND_IR_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

extern Adafruit_SSD1306 display;

const int irSensor1 = 26;
const int irSensor2 = 27;
const int irSensor3 = 14;
const int irSensor4 = 12;
const int irSensor5 = 13;
const int ledPin = 23;

extern int thresholds[5];
extern int lastSensorValues[5];

void initializeDisplayAndSensors();
void runOnce();
void displayCalibrationSquares();
void updateCalibrationSquares(int sensorValues[]);
int calculateThreshold();
void controlMotorsAndBuzzer(int sensorValues[]);
void calibrateRobot();
int calculateThreshold(int sensorPin);

#endif // OLED_AND_IR_H