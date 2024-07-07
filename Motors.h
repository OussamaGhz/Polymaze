#ifndef MOTORS_H
#define MOTORS_H

const int ena = 0;  // Enable pin for motor A
const int enb = 4;  // Enable pin for motor B
const int in1 = 16; // Control pin 1 for motor A
const int in2 = 17; // Control pin 2 for motor A
const int in3 = 18; // Control pin 1 for motor B
const int in4 = 5;  // Control pin 2 for motor B

void initializeMotors();
void forward();
void backward();
void turnLeft();
void turnRight();
void turnBack();
void adjustSpeed(int speedA, int speedB);
void controlMotorsAndBuzzer(int sensorValues[]);

#endif // MOTORS_H
