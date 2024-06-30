#ifndef MOTORS_AND_BUZZER_H
#define MOTORS_AND_BUZZER_H

const int enb = 4;
const int en1 = 16;
const int en2 = 17;
const int en3 = 18;
const int en4 = 5;
const int led = 23;
const int buzzer = 15;

void initializeMotorsAndBuzzer();
void controlMotorsAndBuzzer(int sensorValues[]);

#endif // MOTORS_AND_BUZZER_H
 
