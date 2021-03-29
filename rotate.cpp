#include "rotate.h"
void rotate90R(double* encoderPosR){
    resetEncoder();
    rTime = millis();
    pidTime = millis();
    mySetp = 125;
    double RIN = 0;
    while ((millis() - rTime) <= 2000)
    {
        RIN = myPID.Calculate(mySetp, *encoderPosR);
        if((millis() - pidTime) > 10){
            if(RIN > 0){
                motor_Lui(1, RIN);
                motor_Tien(2, RIN);
                motor_Lui(3, RIN);
                motor_Tien(4, RIN);
            }
            else {
                motor_Tien(1, abs(RIN));
                motor_Lui(2, abs(RIN));
                motor_Tien(3, abs(RIN));
                motor_Lui(4, abs(RIN));
            }
        }
        else{
            pidTime = millis();
        }
    }
    

}

void rotate90L(){

}

void rotate180(){

}
