#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#ifndef READENCODER_H
#define READENCODER_H
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>
#define encodPinA1      2                             
#define encodPinB1      14                             

void readEncoderInit();
void resetEncoder();
void encoder();

#endif
