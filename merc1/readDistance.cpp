#include "readDistance.h"
void readDistanceInit(){
    readTime = millis();
    if (!lox.begin()) {
        disVar = 1;
    }
}

void exportDistance(double& n){
    VL53L0X_RangingMeasurementData_t measure;
    if((millis() - readTime)<= 50){
    lox.rangingTest(&measure, false);

        if (measure.RangeStatus != 4) {
            n = measure.RangeMilliMeter;
        } else {
            n = 1000;
        }
    }   
    else    readTime = millis();
}