//library workspace:
#include <SoftwareSerial.h> //UART lib
//USB host shield lib
#include <PS4BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
//Distance sensor lib
#include <SPI.h>

//Interrupt lib
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

//motor control lib
#include "motor.h"

//include and setup pid
#include "PIDver1.h"
double mySetp = 0;
#define myKp  1000000000
#define myKi  0
#define myKd  0
#define myOutMax  120
#define myOutMin  -120
#define myTime 0.03
PID myPID(myKp, myKi, myKd, myTime, myOutMax, myOutMin,1);

#define encodPinA1      20                             
#define encodPinB1      21  
#define lightPin        A8     

//variable for position of encoder
volatile long encoderPos = 0;
volatile long encoderPosR = 0;
volatile long encoderPosL = 0;
volatile long encoderPosA = 0;

//variable for button timer:
unsigned long upSttTime = 0;
unsigned long downSttTime = 0;
unsigned long leftSttTime = 0;
unsigned long rightSttTime = 0;
unsigned long cirSttTime = 0;
unsigned long crossSttTime = 0;
unsigned long triSttTime = 0;
unsigned long sqrSttTime = 0;

//Variable mode of speedrun:
int upSpeed = 1;
int downSpeed = 1;
int leftSpeed = 1;
int rightSpeed = 1;
int cirSpeed = 1;
int crossSpeed = 1;
int triSpeed = 1;
int sqrSpeed = 1;

//Variable for pid status and timer
unsigned long rTime = 0;
unsigned long lTime = 0;
unsigned long aTime = 0;
unsigned long pidTime = 0;
unsigned long runTime = 0;

//USB initialization
USB Usb;
BTD Btd(&Usb); 
//PS4BT PS4(&Btd, PAIR); //Ket noi lan dau bang cach nhan nut share và nut PS.
PS4BT PS4(&Btd); //Thay lenh phia tren bang lenh nay sau khi ket noi thanh cong, nap lai code, lan sau chi can nhan nut PS de ket noi.

//variable of button status
bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
int tuan;
int R2Stt = 0; 
int L2Stt = 0;
int UpStt = 0;
int DownStt = 0;
int LeftStt = 0;
int RightStt = 0;
int TriStt = 0;
int CirStt = 0;
int CrStt = 0;
int SqrStt = 0;

//init all the button code
void CircleButton(int &cirSpeed, unsigned long &cirSttTime, int &CirpStt);
void TriangleButton(int &triSpeed, unsigned long &triSttTime, int &TriStt);
void ButtonRight(int &rightSpeed, unsigned long &rightSttTime, int &RightStt);
void ButtonLeft(int &leftSpeed, unsigned long &leftSttTime, int &LeftStt);
void ButtonDown(int &downSpeed, unsigned long &downSttTime, int &DownStt);
void ButtonUp(int &upSpeed, unsigned long &upSttTime, int &UpStt);

//setup for all code in main
void setup() {
  Serial.begin(19200);
  pinMode(lightPin,   INPUT);
  pinMode(encodPinA1, INPUT_PULLUP);
  pinMode(encodPinB1, INPUT_PULLUP);
  attachInterrupt(3, encoder, FALLING);
  motorSetup();
  //Reset motor
  motor_Dung(1);
  motor_Dung(2);
  motor_Dung(3);
  motor_Dung(4);
  
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
    Serial.print(F("\r\nPS4 Bluetooth Library Started"));
  while((analogRead(lightPin) < 500));
}

      
void loop() {
  Serial.println(encoderPos);
  Usb.Task();
  if(PS4.connected()) {
    if(     !(PS4.getButtonPress(UP)||PS4.getButtonPress(DOWN)||
            PS4.getButtonPress(RIGHT)||PS4.getButtonPress(LEFT)||
            PS4.getButtonPress(TRIANGLE)||PS4.getButtonPress(CIRCLE))){ 
                  motor_Dung(1);
                  motor_Dung(2);
                  motor_Dung(3);
                  motor_Dung(4);
                  UpStt = 0;
                  DownStt = 0;
                  RightStt = 0;
                  LeftStt = 0;
                  TriStt = 0;
                  CirStt = 0;
                  goto ending;
               }
          if(PS4.getButtonPress(UP)) {ButtonUp(upSpeed, upSttTime, UpStt); goto ending; }
          if (PS4.getButtonPress(DOWN)){ButtonDown(downSpeed, downSttTime, DownStt); goto ending; } 
          if(PS4.getButtonPress(RIGHT)){ ButtonRight(rightSpeed, rightSttTime, RightStt); goto ending;}
          if(PS4.getButtonPress(CIRCLE)){ CircleButton(cirSpeed, cirSttTime, CirStt); goto ending;}
          if(PS4.getButtonPress(LEFT)){ ButtonLeft(leftSpeed, leftSttTime, LeftStt); goto ending;}  
          if(PS4.getButtonPress(TRIANGLE)){ TriangleButton(triSpeed, triSttTime, TriStt); goto ending;}
  }

  ending:
      if (PS4.getButtonClick(L1)){
        Serial.print(F("\r\nL1"));        
            }
}

//Handling Button Circle - rotate left of the robot 
void CircleButton(int &cirSpeed, unsigned long &cirSttTime, int &CirpStt){
  if(CirStt == 0){
    Serial.println(F("\r\LEFT ROTATE"));
    cirSpeed = 1; 
    CirStt = 1;
    cirSttTime = millis();

  }
  switch(cirSpeed){
    case 1:
        motor_Tien(1, 5); 
        motor_Tien(2, 5); 
        motor_Tien(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - cirSttTime) > 30){
          cirSpeed++;
          cirSttTime = millis();
        } 
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Tien(2, 10); 
        motor_Tien(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - cirSttTime) > 30){ 
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Tien(2, 20); 
        motor_Tien(3, 20); 
        motor_Tien(4, 20); 
        if((millis() - cirSttTime) > 30){
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
    case 4:
        motor_Tien(1, 40); 
        motor_Tien(2, 40); 
        motor_Tien(3, 40); 
        motor_Tien(4, 40); 
        if((millis() - cirSttTime) > 50){
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Tien(2, 80); 
        motor_Tien(3, 80); 
        motor_Tien(4, 80); 
        if((millis() - cirSttTime) > 100){
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
    case 6:
        motor_Tien(1, 160); 
        motor_Tien(2, 160); 
        motor_Tien(3, 160); 
        motor_Tien(4, 160);    
    break;
  }
}
//Handling Button Triangle - Rotate Right of the robot
void TriangleButton(int &triSpeed, unsigned long &triSttTime, int &TriStt){    
  if(TriStt == 0){
    Serial.println(F("\r\RIGHT ROTATE"));
    triSpeed = 1; 
    TriStt = 1;
    triSttTime = millis();
  }
  switch(triSpeed){
    case 1:
        motor_Lui(1, 5); 
        motor_Lui(2, 5); 
        motor_Lui(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - triSttTime) > 30){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Lui(2, 10); 
        motor_Lui(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - triSttTime) > 30){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Lui(2, 20); 
        motor_Lui(3, 20); 
        motor_Lui(4, 20); 
        if((millis() - triSttTime) > 30){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Lui(2, 40); 
        motor_Lui(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - triSttTime) > 50){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Lui(2, 80); 
        motor_Lui(3, 80); 
        motor_Lui(4, 80); 
        if((millis() - triSttTime) > 100){
         triSpeed++;
          triSttTime = millis();
        }
    break;
    case 6:
       motor_Lui(1, 160); 
       motor_Lui(2, 160); 
       motor_Lui(3, 160); 
       motor_Lui(4, 160);       
    break;
  }
}
//Handling Button Right - goto the right
void ButtonRight(int &rightSpeed, unsigned long &rightSttTime, int &RightStt){
  if(RightStt == 0){
    Serial.println(F("\r\RIGHT"));
    rightSpeed = 1; 
    RightStt = 1;
    rightSttTime = millis();
  }
  switch(rightSpeed){
    case 1:
        motor_Lui(1, 5); 
        motor_Tien(2, 5); 
        motor_Lui(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 2:
       motor_Lui(1, 10); 
        motor_Tien(2, 10); 
        motor_Lui(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
        rightSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Tien(2, 20); 
        motor_Lui(3, 20); 
        motor_Tien(4,20); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Tien(2, 40); 
        motor_Lui(3, 40); 
        motor_Tien(4, 40);
        if((millis() - rightSttTime) > 50){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Tien(2, 80); 
        motor_Lui(3, 80); 
        motor_Tien(4, 80);
        if((millis() - rightSttTime) > 100){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 6:
        motor_Lui(1, 160); 
        motor_Tien(2, 160); 
        motor_Lui(3, 160); 
        motor_Tien(4, 160);
    break;
  }
}
//Handling Button Left - goto the left
void ButtonLeft(int &leftSpeed, unsigned long &leftSttTime, int &LeftStt){
  if(LeftStt == 0){
    Serial.println(F("\r\LEFT"));
    leftSpeed = 1; 
    LeftStt = 1;
    leftSttTime = millis();
  }
  switch(leftSpeed){
    case 1:
        motor_Tien(1, 5); 
        motor_Lui(2, 5); 
        motor_Tien(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Lui(2, 10); 
        motor_Tien(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Lui(2, 20); 
        motor_Tien(3, 20); 
        motor_Lui(4, 20); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
     case 4:
        motor_Tien(1, 40); 
        motor_Lui(2, 40); 
        motor_Tien(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - leftSttTime) > 50){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Lui(2, 80); 
        motor_Tien(3, 80); 
        motor_Lui(4, 80); 
        if((millis() - leftSttTime) > 100){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 6:
        motor_Tien(1, 160); 
        motor_Lui(2, 160); 
        motor_Tien(3, 160); 
        motor_Lui(4, 160); 
    break;
    
  }
}
//Handling Button Down = go down of the robot
void ButtonDown(int &downSpeed, unsigned long &downSttTime, int &DownStt){
  if(DownStt == 0){
    Serial.println(F("\r\DOWN"));
    downSpeed = 1; 
    DownStt = 1;
    downSttTime = millis();
  }

  switch(downSpeed){
    case 1:
        motor_Lui(1, 5); 
        motor_Lui(2, 5); 
        motor_Tien(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Lui(2, 10); 
        motor_Tien(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Lui(2, 20); 
        motor_Tien(3, 20); 
        motor_Tien(4, 20); 
        if((millis() - downSttTime) > 30){
         downSpeed++;
          downSttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Lui(2, 40); 
        motor_Tien(3, 40); 
        motor_Tien(4, 40); 
        if((millis() - downSttTime) > 50){
         downSpeed++;
         downSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Lui(2, 80); 
        motor_Tien(3, 80); 
        motor_Tien(4, 80); 
        if((millis() - downSttTime) > 100){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 6:
        motor_Lui(1, 160); 
        motor_Lui(2, 160); 
        motor_Tien(3, 160); 
        motor_Tien(4, 160); 
    break;
  }    
}
//Handling Button Up = go up of the robot
void ButtonUp(int &upSpeed, unsigned long &upSttTime, int &UpStt){
  if(UpStt == 0){
    Serial.println(F("\r\nUP"));
    upSpeed = 1; 
    UpStt = 1;
    upSttTime = millis();
  }
  switch(upSpeed){
    case 1:
        motor_Tien(1, 5); 
        motor_Tien(2, 5); 
        motor_Lui(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - upSttTime) > 30){
          upSpeed++;
          upSttTime = millis();
        }
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Tien(2, 10); 
        motor_Lui(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - upSttTime) > 30){
          upSpeed++;
          upSttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Tien(2, 20); 
        motor_Lui(3, 20); 
        motor_Lui(4, 20); 
        if((millis() - upSttTime) > 30){
          upSpeed++;
          upSttTime = millis();
        }
    break;
     case 4:
        motor_Tien(1, 40); 
        motor_Tien(2, 40); 
        motor_Lui(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - upSttTime) > 50){
          upSpeed++;
          upSttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Tien(2, 80); 
        motor_Lui(3, 80); 
        motor_Lui(4, 80); 
        if((millis() - upSttTime) > 100){
          upSpeed++;
          upSttTime = millis();
        }       
    break;
    case 6:
        motor_Tien(1, 160); 
        motor_Tien(2, 160); 
        motor_Lui(3, 160); 
        motor_Lui(4, 160);      
    break;
  }        

}

void upAuto(){
  mySetp = 1500;
  pidTime = millis();
  runTime = millis();
  double pidSpeed = 0;
  encoderPos = 0;
  while ((millis() - runTime) < 20000)
   {
      if(pidSpeed > 0){
        motor_Lui(1, pidSpeed);
        motor_Lui(2, pidSpeed);
        motor_Tien(3, pidSpeed);
        motor_Tien(4, pidSpeed);
      }
      else {
        motor_Tien(1, abs(pidSpeed));
        motor_Tien(2, abs(pidSpeed));
        motor_Lui(3, abs(pidSpeed));
        motor_Lui(4, abs(pidSpeed));
      }
       if((millis() - pidTime) > 30){
          pidSpeed = myPID.Calculate(mySetp, encoderPos);
          pidTime = millis();
       }  
   }   
}

void downAuto(){
  mySetp = -1500;
  pidTime = millis();
  runTime = millis();
  double pidSpeed = 0;
  encoderPos = 0;
  while ((millis() - runTime) < 20000)
   {
      if(pidSpeed > 0){
        motor_Lui(1, pidSpeed);
        motor_Lui(2, pidSpeed);
        motor_Tien(3, pidSpeed);
        motor_Tien(4, pidSpeed);
      }
      else {
        motor_Tien(1, abs(pidSpeed));
        motor_Tien(2, abs(pidSpeed));
        motor_Lui(3, abs(pidSpeed));
        motor_Lui(4, abs(pidSpeed));
      }
       if((millis() - pidTime) > 30){
          pidSpeed = myPID.Calculate(mySetp, encoderPos);
          pidTime = millis();
       }  
   }   
}

void leftAuto(){
  mySetp = 260;
  pidTime = millis();
  runTime = millis();
  double pidSpeed = 0;
  encoderPos = 0;
  while ((millis() - runTime) < 20000)
   {
      if(pidSpeed > 0){
        motor_Tien(1, pidSpeed);
        motor_Lui(2, pidSpeed);
        motor_Tien(3, pidSpeed);
        motor_Lui(4, pidSpeed);
      }
      else {
        motor_Lui(1, abs(pidSpeed));
        motor_Tien(2, abs(pidSpeed));
        motor_Lui(3, abs(pidSpeed));
        motor_Tien(4, abs(pidSpeed));
      }
       if((millis() - pidTime) > 30){
          pidSpeed = myPID.Calculate(mySetp, encoderPos);
          pidTime = millis();
       }  
   }   
}

void rightAuto(){
  mySetp = 260;
  pidTime = millis();
  runTime = millis();
  double pidSpeed = 0;
  encoderPos = 0;
  while ((millis() - runTime) < 20000)
   {
      if(pidSpeed > 0){
        motor_Lui(1, pidSpeed);
        motor_Tien(2, pidSpeed);
        motor_Lui(3, pidSpeed);
        motor_Tien(4, pidSpeed);
      }
      else {
        motor_Tien(1, abs(pidSpeed));
        motor_Lui(2, abs(pidSpeed));
        motor_Tien(3, abs(pidSpeed));
        motor_Lui(4, abs(pidSpeed));
      }
       if((millis() - pidTime) > 30){
          pidSpeed = myPID.Calculate(mySetp, encoderPos);
          pidTime = millis();
       }  
   }   
}

void R90Auto(){
  mySetp = 175;
  pidTime = millis();
  runTime = millis();
  double pidSpeed = 0;
  encoderPos = 0;
  while ((millis() - runTime) < 20000)
   {
      if(pidSpeed > 0){
        motor_Lui(1, pidSpeed);
        motor_Lui(2, pidSpeed);
        motor_Lui(3, pidSpeed);
        motor_Lui(4, pidSpeed);
      }
      else {
        motor_Tien(1, abs(pidSpeed));
        motor_Tien(2, abs(pidSpeed));
        motor_Tien(3, abs(pidSpeed));
        motor_Tien(4, abs(pidSpeed));
      }
       if((millis() - pidTime) > 30){
          pidSpeed = myPID.Calculate(mySetp, encoderPos);
          pidTime = millis();
       }  
   }   
}

void L90Auto(){
  mySetp = 175;
  pidTime = millis();
  runTime = millis();
  double pidSpeed = 0;
  encoderPos = 0;
  while ((millis() - runTime) < 20000)
   {
      if(pidSpeed > 0){
        motor_Tien(1, pidSpeed);
        motor_Tien(2, pidSpeed);
        motor_Tien(3, pidSpeed);
        motor_Tien(4, pidSpeed);
      }
      else {
        motor_Lui(1, abs(pidSpeed));
        motor_Lui(2, abs(pidSpeed));
        motor_Lui(3, abs(pidSpeed));
        motor_Lui(4, abs(pidSpeed));
      }
       if((millis() - pidTime) > 30){
          pidSpeed = myPID.Calculate(mySetp, encoderPos);
          pidTime = millis();
       }  
   }   
}

void A180Auto(){
  mySetp = 360;
  pidTime = millis();
  runTime = millis();
  double pidSpeed = 0;
  encoderPos = 0;
  while ((millis() - runTime) < 20000)
   {
      if(pidSpeed > 0){
        motor_Lui(1, pidSpeed);
        motor_Lui(2, pidSpeed);
        motor_Lui(3, pidSpeed);
        motor_Lui(4, pidSpeed);
      }
      else {
        motor_Tien(1, abs(pidSpeed));
        motor_Tien(2, abs(pidSpeed));
        motor_Tien(3, abs(pidSpeed));
        motor_Tien(4, abs(pidSpeed));
      }
       if((millis() - pidTime) > 30){
          pidSpeed = myPID.Calculate(mySetp, encoderPos);
          pidTime = millis();
       }  
   }   
}

void encoder()  {                                     
 if ((digitalRead(encodPinB1) == 1))    {
   encoderPos++;   
   encoderPosR++;
   encoderPosL++;
   encoderPosA++;
 }      
 else{
   encoderPos--;   
   encoderPosR--;
   encoderPosL--;
   encoderPosA--;  
 }     
}
