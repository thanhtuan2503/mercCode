
#include <SoftwareSerial.h>
#include <PS4BT.h>
#include "motor.h"
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
unsigned long previousMillis = 0;  
//variable for button timer:
unsigned long upSttTime = 0;
unsigned long downSttTime = 0;
unsigned long leftSttTime = 0;
unsigned long rightSttTime = 0;
unsigned long cirSttTime = 0;
unsigned long crossSttTime = 0;
unsigned long triSttTime = 0;
unsigned long sqrSttTime = 0;
//
//Mode of speedrun:
int upSpeed = 1;
int downSpeed = 1;
int leftSpeed = 1;
int rightSpeed = 1;
int cirSpeed = 1;
int crossSpeed = 1;
int triSpeed = 1;
int sqrSpeed = 1;
//
const long interval = 4000;

USB Usb;
//USBHub Hub1(&Usb); // Some donglesBTD Btd(&Usb);
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

//PS4BT PS4(&Btd, PAIR); //Ket noi lan dau bang cach nhan nut share và nut PS.

PS4BT PS4(&Btd); //Thay lenh phia tren bang lenh nay sau khi ket noi thanh cong, nap lai code, lan sau chi can nhan nut PS de ket noi.
//SoftwareSerial mySerial(10, 11);
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


void setup() {
  Serial.begin(19200);
  motorSetup();
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
    Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}
void ButtonUp(int &upSpeed, unsigned long &upSttTime, int &UpStt){
  if(UpStt == 0){
    Serial.println(F("\r\nUP"));
    upSpeed = 1; 
    UpStt = 1;
    upSttTime = millis();
  }
//        motor_Tien(1, 160); 
//        motor_Tien(2, 160); 
//        motor_Tien(3, 160); 
//        motor_Tien(4, 160); 
  switch(upSpeed){
    case 1:
        motor_Tien(1, 5); 
        motor_Tien(2, 5); 
        motor_Tien(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - upSttTime) > 30){
          upSpeed++;
          upSttTime = millis();
        } 
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Tien(2, 10); 
        motor_Tien(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - upSttTime) > 30){ 
          upSpeed++;
          upSttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Tien(2, 20); 
        motor_Tien(3, 20); 
        motor_Tien(4, 20); 
        if((millis() - upSttTime) > 30){
          upSpeed++;
          upSttTime = millis();
        }
    break;
    case 4:
        motor_Tien(1, 40); 
        motor_Tien(2, 40); 
        motor_Tien(3, 40); 
        motor_Tien(4, 40); 
        if((millis() - upSttTime) > 30){
          upSpeed++;
          upSttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Tien(2, 80); 
        motor_Tien(3, 80); 
        motor_Tien(4, 80); 
    break;
  }
}

//Handling Button Down******************************

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
        motor_Lui(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Lui(2, 10); 
        motor_Lui(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Lui(2, 20); 
        motor_Lui(3, 20); 
        motor_Lui(4, 20); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Lui(2, 40); 
        motor_Lui(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Lui(2, 80); 
        motor_Lui(3, 80); 
        motor_Lui(4, 80); 
    break;
  }
}

//Handling Button Right******************************
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
        motor_Tien(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Tien(2, 10); 
        motor_Tien(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
        rightSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Tien(2, 20); 
        motor_Tien(3, 20); 
        motor_Lui(4, 20); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Tien(2, 40); 
        motor_Tien(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Tien(2, 80); 
        motor_Tien(3, 80); 
        motor_Lui(4, 80); 
    break;
  }
}

//Handling Button Left******************************

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
        motor_Lui(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Lui(2, 10); 
        motor_Lui(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Lui(2, 20); 
        motor_Lui(3, 20); 
        motor_Tien(4, 20); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
     case 4:
        motor_Tien(1, 40); 
        motor_Lui(2, 40); 
        motor_Lui(3, 40); 
        motor_Tien(4, 40); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Lui(2, 80); 
        motor_Lui(3, 80); 
        motor_Tien(4, 80); 
    break;
  }
}

//Handling Button Triangle******************************

void TriangleButton(int &triSpeed, unsigned long &triSttTime, int &TriStt){    //xoay phải
  if(TriStt == 0){
    Serial.println(F("\r\RIGHT ROTATE"));
    triSpeed = 1; 
    TriStt = 1;
    triSttTime = millis();
  }
  switch(triSpeed){
    case 1:
        motor_Tien(1, 5); 
        motor_Lui(2, 5); 
        motor_Tien(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - triSttTime) > 30){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Lui(2, 10); 
        motor_Tien(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - triSttTime) > 30){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Lui(2, 20); 
        motor_Tien(3, 20); 
        motor_Lui(4, 20); 
        if((millis() - triSttTime) > 30){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 4:
        motor_Tien(1, 40); 
        motor_Lui(2, 40); 
        motor_Tien(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - triSttTime) > 30){
          triSpeed++;
          triSttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Lui(2, 80); 
        motor_Tien(3, 80); 
        motor_Lui(4, 80); 
    break;
  } 
      
      
}
//Handling Button Circle******************************
void CircleButton(int &cirSpeed, unsigned long &cirSttTime, int &CirpStt){    //xoay trái
  if(CirStt == 0){
    Serial.println(F("\r\LEFT ROTATE"));
    cirSpeed = 1; 
    CirStt = 1;
    cirSttTime = millis();
  }
  switch(cirSpeed){
    case 1:
        motor_Lui(1, 5); 
        motor_Tien(2, 5); 
        motor_Lui(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - cirSttTime) > 30){
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Tien(2, 10); 
        motor_Lui(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - cirSttTime) > 30){
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Tien(2, 20); 
        motor_Lui(3, 20); 
        motor_Tien(4, 20); 
        if((millis() - cirSttTime) > 30){
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
     case 4:
        motor_Lui(1, 40); 
        motor_Tien(2, 40); 
        motor_Lui(3, 40); 
        motor_Tien(4, 40); 
        if((millis() - cirSttTime) > 30){
          cirSpeed++;
          cirSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Tien(2, 80); 
        motor_Lui(3, 80); 
        motor_Tien(4, 80); 
    break;
  }        

}
      
/*
//Handling Button Cross******************************
void CrossButton(){
        if (PS4.getButtonPress(CROSS)) {
        while ( CrStt != 1){
          Serial.print(F("\r\nCross"));
          send_data_uart(1,1,254);//dir 1
          send_data_uart(1,2,0);
          send_data_uart(1,4,0);
          send_data_uart(1,8,0);
          CrStt = 1;
        }
      }
      else {
        while ( CrStt != 0){
            send_data_uart(0,1,0);
            send_data_uart(0,2,0);
            send_data_uart(0,4,0);
            send_data_uart(0,8,0);
         CrStt = 0;
        }
      }  
}
//Handling Button Square******************************
void SquareButton(){
  
      if (PS4.getButtonPress(SQUARE)) {
        while ( SqrStt != 1){
          Serial.print(F("\r\nSquare"));
          send_data_uart(1,1,0);
          send_data_uart(1,2,0);
          send_data_uart(1,4,0);
          send_data_uart(1,8,254);//dir 1
          SqrStt = 1;   
        }
      }
      else{
        while ( SqrStt != 0){
         
            send_data_uart(0,1,0);
            send_data_uart(0,2,0);
            send_data_uart(0,4,0);
            send_data_uart(0,8,0);
          SqrStt = 0;
        }   
      }
}
//Handling Button L2******************************
void L2Button(){
       if (PS4.getButtonPress(L2)) {
        while ( L2Stt != 1){      
          send_data_uart(1,1,125);//dir 1
          send_data_uart(1,2,125);//1
          send_data_uart(1,4,125);//1
          send_data_uart(1,8,125);//1
          L2Stt = 1;
        }
      }
      else {
        while( L2Stt != 0){
          
            send_data_uart(0,1,0);
            send_data_uart(0,2,0);
            send_data_uart(0,4,0);
            send_data_uart(0,8,0);
          L2Stt = 0;
        }
      }
}
//Handling Button R2******************************
void R2Button(){
        if (PS4.getButtonPress(R2)) {
        while ( R2Stt != 1){      
         send_data_uart(0,1,125);//dir 0
          send_data_uart(0,2,125);//0
          send_data_uart(0,4,125);//0
          send_data_uart(0,8,125);//0
          R2Stt = 1;
        }
      }
      else {
        while( R2Stt != 0){
  
            send_data_uart(0,1,0);
            send_data_uart(0,2,0);
            send_data_uart(0,4,0);
            send_data_uart(0,8,0);
          R2Stt = 0;
        }
      }
}*/
void loop() {
  
  Usb.Task();
//  unsigned long currentMillis = millis();
  if(PS4.connected()) {
    if(PS4.getButtonPress(UP)||PS4.getButtonPress(DOWN)||PS4.getButtonPress(RIGHT)||PS4.getButtonPress(LEFT)||PS4.getButtonPress(TRIANGLE)||PS4.getButtonPress(CIRCLE)) ;
      else { 
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
          if(PS4.getButtonPress(UP)) {
            ButtonUp(upSpeed, upSttTime, UpStt); 
            goto ending;
           }
          if (PS4.getButtonPress(DOWN)){ButtonDown(downSpeed, downSttTime, DownStt); goto ending; } 
          if(PS4.getButtonPress(RIGHT)){ ButtonRight(rightSpeed, rightSttTime, RightStt); goto ending;}
          if(PS4.getButtonPress(CIRCLE)){ CircleButton(cirSpeed, cirSttTime, CirStt); goto ending;}
          if(PS4.getButtonPress(LEFT)){ ButtonLeft(leftSpeed, leftSttTime, LeftStt); goto ending;}  
          if(PS4.getButtonPress(TRIANGLE)){ TriangleButton(triSpeed, triSttTime, TriStt); goto ending;}
  }
// if (mySerial.available()) {
//    Serial.write(mySerial.read());
   // Serial.write("hello");
  //}
//    
//    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
//      Serial.print(F("\r\nLeftHatX: "));
//      Serial.print(PS4.getAnalogHat(LeftHatX));
//      Serial.print(F("\tLeftHatY: "));
//      Serial.print(PS4.getAnalogHat(LeftHatY));
//      Serial.print(F("\tRightHatX: "));
//      Serial.print(PS4.getAnalogHat(RightHatX));
//      Serial.print(F("\tRightHatY: "));
//      Serial.print(PS4.getAnalogHat(RightHatY));
//    }
//
//    if (PS4.getAnalogButton(L2) || PS4.getAnalogButton(R2)) { // These are the only analog buttons on the PS4 controller
//      Serial.print(F("\r\nL2: "));
//      Serial.print(PS4.getAnalogButton(L2));
//      Serial.print(F("\tR2: "));
//      Serial.print(PS4.getAnalogButton(R2));
//    }
//    //Handling Analog Button*****************************************************
//   // L2Button();
//   // R2Button(); 
//    //***************************************************************************
//
//    if (PS4.getButtonClick(PS)) {
//      Serial.print(F("\r\nPS"));
//      PS4.disconnect();
//    }
//    else {
//
//    // Directional Button******************************
//    
//    if(PS4.getButtonPress(UP)) {ButtonUp(); goto ending;}
//    if (PS4.getButtonPress(DOWN)){ButtonDown(); goto ending; } 
//    if(PS4.getButtonPress(RIGHT)){ ButtonRight(); goto ending;}
//    if(PS4.getButtonPress(CIRCLE)){ CircleButton(); goto ending;}
//    if(PS4.getButtonPress(LEFT)){ ButtonLeft(); goto ending;}  
//    if(PS4.getButtonPress(TRIANGLE)){ TriangleButton(); goto ending;}
//                
//            
//    
//   
//    
//
//    //Cubes Button******************************
//   /* TriangleButton();
//    CircleButton();
//    CrossButton();
//    SquareButton();*/
////***********************************************************************
  ending:
    // Serial.println("Ending now!!");

      if (PS4.getButtonClick(L1)){
        Serial.print(F("\r\nL1"));         

            }
//      if (PS4.getButtonClick(L3)){
//        Serial.print(F("\r\nL3"));
//      }
//      if (PS4.getButtonClick(R1)){
//        Serial.print(F("\r\nR1"));
//         
//
//          }
//      if (PS4.getButtonClick(R3)){
//        Serial.print(F("\r\nR3"));
//      }
//      if (PS4.getButtonClick(SHARE)){
//        Serial.print(F("\r\nShare"));
//      }
//      if (PS4.getButtonClick(OPTIONS)) {
//        Serial.print(F("\r\nOptions"));
//        printAngle = !printAngle;
//      }
//      if (PS4.getButtonClick(TOUCHPAD)) {
//        Serial.print(F("\r\nTouchpad"));
//        printTouch = !printTouch;
//      }
//
//      if (printAngle) { // Print angle calculated using the accelerometer only
//        Serial.print(F("\r\nPitch: "));
//        Serial.print(PS4.getAngle(Pitch));
//        Serial.print(F("\tRoll: "));
//        Serial.print(PS4.getAngle(Roll));
//      }
//
//      if (printTouch) { // Print the x, y coordinates of the touchpad
//        if (PS4.isTouching(0) || PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
//          Serial.print(F("\r\n"));
//        for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
//          if (PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
//            Serial.print(F("X")); Serial.print(i + 1); Serial.print(F(": "));
//            Serial.print(PS4.getX(i));
//            Serial.print(F("\tY")); Serial.print(i + 1); Serial.print(F(": "));
//            Serial.print(PS4.getY(i));
//            Serial.print(F("\t"));
//            
//          }
//        }
//      }
//    }
//   }
}
