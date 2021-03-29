#include "readEncoder.h"
double* encoderPos;
double* encoderPosR;
double* encoderPosL;
double* encoderPosA;

void readEncoderInit() {
  pinMode(encodPinA1, INPUT_PULLUP);
  pinMode(encodPinB1, INPUT_PULLUP);
  attachInterrupt(0, encoder, FALLING);
  TCCR1B = TCCR1B & 0b11111000 | 1;
}
void resetEncoder(double* encoderPos, double* encoderPosR, double* encoderPosL,double* encoderPosA){
    *encoderPos = 0;   
    *encoderPosR = 0;
    *encoderPosL = 0;
    *encoderPosA = 0;
}
void encoder(double* encoderPos, double* encoderPosR, double* encoderPosL,double* encoderPosA)  {                                     
  if (PINB & 0b00000001)    {
    *encoderPos++;   
    *encoderPosR++;
    *encoderPosL++;
    *encoderPosA++;
  }      
  else{
    *encoderPos++;   
    *encoderPosR++;
    *encoderPosL++;
    *encoderPosA++;  
  }     
}
