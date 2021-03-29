#ifndef READDISTANCE_H
#define READDISTANCE_H
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int disVar = 0;
unsigned long readTime = 0;
void readEncoderInit();
void exportDistance(int* n);

#endif