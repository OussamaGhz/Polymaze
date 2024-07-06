#ifndef MOTORS_H
#define MOTORS_H

const int ena = 0;
const int enb = 4;
const int in1 = 16;
const int in2 = 17;
const int in3 = 18;
const int in4 = 5;



void initializeMotors();
void forward();
void backward();
void turnLeft();
void turnRight();
void turnBack();
void adjustSpeed(int speedA,int speedB);

#endif // MOTORS_H
 
