//#include "rotate.h"
//void rotate90R(double encoderPosR){
//    rTime = millis();
//    pidTime = millis();
//    mySetp = 125;
//    double RIN = 0;
//    while ((millis() - rTime) <= 2000)
//    {
//        RIN = myPID.Calculate(mySetp, encoderPosR);
//        if((millis() - pidTime) > 10){
//            if(RIN > 0){
//                motor_Lui(1, RIN);
//                motor_Lui(2, RIN);
//                motor_Lui(3, RIN);
//                motor_Lui(4, RIN);
//            }
//            else {
//                motor_Tien(1, abs(RIN));
//                motor_Tien(2, abs(RIN));
//                motor_Tien(3, abs(RIN));
//                motor_Tien(4, abs(RIN));
//            }
//        }
//        else{
//            pidTime = millis();
//        }
//    }
//    
//
//}
//
//void rotate90L(double encoderPosL){
//    lTime = millis();
//    pidTime = millis();
//    mySetp = -125;
//    double RIN = 0;
//    while ((millis() - lTime) <= 2000)
//    {
//        RIN = myPID.Calculate(mySetp, encoderPosL);
//        if((millis() - pidTime) > 10){
//            if(RIN > 0){
//                motor_Tien(1, RIN);
//                motor_Tien(2, RIN);
//                motor_Tien(3, RIN);
//                motor_Tien(4, RIN);
//            }
//            else {
//                motor_Lui(1, abs(RIN));
//                motor_Lui(2, abs(RIN));
//                motor_Lui(3, abs(RIN));
//                motor_Lui(4, abs(RIN));
//            }
//        }
//        else{
//            pidTime = millis();
//        }
//    }
//}
//
//void rotate180(double encoderPosA){
//    aTime = millis();
//    pidTime = millis();
//    mySetp = 250;
//    double RIN = 0;
//    while ((millis() - aTime) <= 2000)
//    {
//        RIN = myPID.Calculate(mySetp, encoderPosA);
//        if((millis() - pidTime) > 10){
//            if(RIN > 0){
//                motor_Lui(1, RIN);
//                motor_Lui(2, RIN);
//                motor_Lui(3, RIN);
//                motor_Lui(4, RIN);
//            }
//            else {
//                motor_Tien(1, abs(RIN));
//                motor_Tien(2, abs(RIN));
//                motor_Tien(3, abs(RIN));
//                motor_Tien(4, abs(RIN));
//            }
//        }
//        else{
//            pidTime = millis();
//        }
//    }
//}
//void runAndDetach(double &encoderPos, double &encoderPosR, double &encoderPosL,double &encoderPosA){
//    runTime = millis();
//    pidTime = millis();
//    mySetp = 1000;
//    double RIN = 0;
//    while ((millis() - runTime) < 3000)
//    {
//        RIN = myPID.Calculate(mySetp, encoderPos);
//        if((millis() - pidTime) > 10){
//            if(RIN > 0){
//                motor_Tien(1, RIN);
//                motor_Tien(2, RIN);
//                motor_Tien(3, RIN);
//                motor_Tien(4, RIN);
//            }
//            else {
//                motor_Lui(1, abs(RIN));
//                motor_Lui(2, abs(RIN));
//                motor_Lui(3, abs(RIN));
//                motor_Lui(4, abs(RIN));
//            }
//        }
//        else{
//            pidTime = millis();
//        }       
//    }
//    readDistanceInit();
//    runTime = millis();
//    pidTime = millis();
//    mySetp = 50;
//    double disT = 0;
//    while ((millis() - runTime) < 3000)
//    {
//        RIN = myPID.Calculate(mySetp, disT);
//        if((millis() - pidTime) > 10){
//            exportDistance(disT);
//            if(RIN > 0){
//                motor_Tien(1, RIN);
//                motor_Tien(2, RIN);
//                motor_Tien(3, RIN);
//                motor_Tien(4, RIN);
//            }
//            else {
//                motor_Lui(1, abs(RIN));
//                motor_Lui(2, abs(RIN));
//                motor_Lui(3, abs(RIN));
//                motor_Lui(4, abs(RIN));
//            }
//        }
//        else{
//            pidTime = millis();
//        }       
//    }
//    /*Code gắp vật
//
//
//    */
//   //Code xoay ngay tầm 20cm
//    runTime = millis();
//    pidTime = millis();
//    mySetp = 300;
//    resetEncoder(double &encoderPos, double &encoderPosR, double &encoderPosL,double &encoderPosA);
//    double RIN = 0;
//    while ((millis() - runTime) < 2000)
//    {
//        RIN = myPID.Calculate(mySetp, encoderPos);
//        if((millis() - pidTime) > 10){
//            if(RIN > 0){
//                motor_Tien(1, RIN);
//                motor_Lui(2, RIN);
//                motor_Tien(3, RIN);
//                motor_Lui(4, RIN);
//            }
//            else {
//                motor_Lui(1, abs(RIN));
//                motor_Tien(2, abs(RIN));
//                motor_Lui(3, abs(RIN));
//                motor_Tien(4, abs(RIN));
//            }
//        }
//        else{
//            pidTime = millis();
//        }       
//    }   
//
//    //Code chạy thẳng tầm 50cm
//    runTime = millis();
//    pidTime = millis();
//    mySetp = 1000;
//    resetEncoder(double &encoderPos, double &encoderPosR, double &encoderPosL,double &encoderPosA);
//    double RIN = 0;
//    while ((millis() - runTime) < 2000)
//    {
//        RIN = myPID.Calculate(mySetp, encoderPos);
//        if((millis() - pidTime) > 10){
//            if(RIN > 0){
//                motor_Tien(1, RIN);
//                motor_Tien(2, RIN);
//                motor_Lui(3, RIN);
//                motor_Lui(4, RIN);
//            }
//            else {
//                motor_Lui(1, abs(RIN));
//                motor_Lui(2, abs(RIN));
//                motor_Tien(3, abs(RIN));
//                motor_Tien(4, abs(RIN));
//            }
//        }
//        else{
//            pidTime = millis();
//        }       
//    }   
//}
