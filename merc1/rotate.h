#ifndef ROTATE_H
#define ROTATE_H
#include "Arduino.h"
#include "motor.h"
#include "PIDver1.h"
#include "readEncoder.h"
#include "readDistance.h"
double mySetp = 0;
#define myKp  10
#define myKi  0
#define myKd  0
#define myOutMax  255
#define myOutMin  0
#define myTime 0.01
PID myPID(myKp, myKi, myKd, myTime, myOutMax, myOutMin,1);

unsigned long rTime = 0;
unsigned long lTime = 0;
unsigned long aTime = 0;
unsigned long pidTime = 0;
unsigned long runTime = 0;
void rotate90R(double encoderPosR);
void rotate90L(double encoderPosL);
void rotate180(double encoderPosA);
void runAndDetach(double encoderPos);

#endif
