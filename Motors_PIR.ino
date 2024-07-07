// #include "Motors.h"
// #include "OledAndIR.h"

// const int baseSpeed = 75;
// const int thresholds[5] = {500, 500, 500, 500, 500}; // Example thresholds

// // PID constants (initial values, need tuning)
// const float Kp = 0.1;
// const float Ki = 0.01;
// const float Kd = 0.05;

// // Variables for PID control
// float previousError = 0;
// float integralError = 0;
// float derivativeError = 0;

// void initializeMotors() {
//   pinMode(ena, OUTPUT);
//   pinMode(enb, OUTPUT);
//   pinMode(in1, OUTPUT);
//   pinMode(in2, OUTPUT);
//   pinMode(in3, OUTPUT);
//   pinMode(in4, OUTPUT);
//   pinMode(led, OUTPUT);
// }

// void adjustSpeed(int speedA, int speedB) {
//   analogWrite(ena, speedA);
//   analogWrite(enb, speedB);
// }

// void backward() {
//   digitalWrite(in1, HIGH);
//   digitalWrite(in2, LOW);
//   digitalWrite(in3, LOW);
//   digitalWrite(in4, HIGH);
// }

// void forward() {
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, HIGH);
//   digitalWrite(in3, HIGH);
//   digitalWrite(in4, LOW);
// }

// void turnLeft() {
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, HIGH);
//   digitalWrite(in3, LOW);
//   digitalWrite(in4, LOW);
// }

// void turnRight() {
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, LOW);
//   digitalWrite(in3, HIGH);
//   digitalWrite(in4, LOW);
// }

// void turnBack() {
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, HIGH);
//   digitalWrite(in3, LOW);
//   digitalWrite(in4, HIGH);
// }

// void controlMotorsAndBuzzer(int sensorValues[]) {
//   // Read sensors
//   int leftMost = analogRead(irSensor1);
//   int left = analogRead(irSensor2);
//   int center = analogRead(irSensor3);
//   int right = analogRead(irSensor4);
//   int rightMost = analogRead(irSensor5);

//   // Calculate error (deviation from desired position)
//   float error = (leftMost * (-3) + left * (-2) + center * 0 + right * 2 + rightMost * 3) / (leftMost + left + center + right + rightMost);

//   // Proportional term
//   float P = Kp * error;

//   // Integral term
//   integralError += error;
//   float I = Ki * integralError;

//   // Derivative term
//   derivativeError = error - previousError;
//   previousError = error;
//   float D = Kd * derivativeError;

//   // PID output
//   float PID_output = P + I + D;

//   // Adjust motor speeds based on PID output
//   int speedA = baseSpeed + PID_output;
//   int speedB = baseSpeed - PID_output;
//   adjustSpeed(speedA, speedB);

//   // Line following logic (can be adjusted based on PID output)
//   if (center > thresholds[2]) {
//     forward();
//   } else if (left > thresholds[1] && center <= thresholds[2]) {
//     turnLeft();
//   } else if (right > thresholds[3] && center <= thresholds[2]) {
//     turnRight();
//   } else if (leftMost > thresholds[0] && left <= thresholds[1]) {
//     turnLeft();
//   } else if (rightMost > thresholds[4] && right <= thresholds[3]) {
//     turnRight();
//   } else if (leftMost <= thresholds[0] && left <= thresholds[1] && center <= thresholds[2] && right <= thresholds[3] && rightMost <= thresholds[4]) {
//     turnBack();
//   }
// }
