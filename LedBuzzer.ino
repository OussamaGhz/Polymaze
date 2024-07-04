#include "LedBuzzer.h"

void initializeLedBuzzer(){
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
}


void LedON(){
  digitalWrite(led,1);
}
void LedOFF(){
  digitalWrite(led,0);
}
void BuzzON(){
  digitalWrite(buzzer,1);
}
void BuzzOFF(){
  digitalWrite(buzzer,0);
}
