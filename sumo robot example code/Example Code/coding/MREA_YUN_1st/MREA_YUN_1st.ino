#include "Ultrasonic.h"

Ultrasonic USF_R (9,8);//Trigger = pin 12, Echo = pin 13
Ultrasonic USF_L (3,2);
Ultrasonic USB_L (11,10);
Ultrasonic USB_R (12,13); 
                 
//int vin = 5;//

/* declare for Ultrasonic */ 

int USFR;
int USFL;
int USBR;
int USBL;

/* declare for IR line sensor */
int IRFR = A0;
int IRFL = A1;
int IRBR = A2;
int IRBL = A3;
int IRFR_c;
int IRFL_c;
int IRBR_c;
int IRBL_c;


//MOTOR DRIVER 1 FRONT

//Assign pins for Motor 
int EL = 6; //PWM1 pin grey
int ML1 = 7; //DIR1 pin purple

//Assign pins for Motor  
int ER = 5;  //PWM2 pin black
int MR1 = 4;  //DIR2 pin white  

int detectRange = 50;
int spdPush = 255;
int spdRotate = (spdPush * (1/2)); 

void setup() 
{
    Serial.begin(9600);
    /*    
    pinMode(vin,OUTPUT);
    digitalWrite(vin,HIGH);
    */
    pinMode(IRFR, INPUT);
    pinMode(IRFL, INPUT);
    pinMode(IRBR, INPUT);
    pinMode(IRBL, INPUT);
    
    pinMode(ER, OUTPUT);
    pinMode(ML1,  OUTPUT);
    pinMode(EL, OUTPUT);
    pinMode(MR1,  OUTPUT);
    
}

//----------------------Functions to define movement---------------------//

void Stop()
{
  analogWrite(EL, 0);
  analogWrite(ER, 0);
}

void Forward(int SForward)
{
  analogWrite(EL, SForward);
  analogWrite(ER, SForward);
  
  digitalWrite (ML1, 1);
  digitalWrite (MR1, 1);   
}

void Backward(int SBackward)
{
  analogWrite(EL, SBackward);
  analogWrite(ER, SBackward);
   
  digitalWrite (ML1, 0);
  digitalWrite (MR1, 0);   
 }

  void GoLeft(int SLeft)
{
  analogWrite(EL, SLeft);
  analogWrite(ER, SLeft);
  
  digitalWrite (ML1, 0);
  digitalWrite (MR1, 1);   
}

  void GoRight(int SRight)
{
  analogWrite(EL, SRight);
  analogWrite(ER, SRight);
  
  digitalWrite (ML1, 1);
  digitalWrite (MR1, 0);   
}
/*------------------------------------------------------------------------------*/


void loop()
{ 
      /* read ultrasonic */
      USFR = USF_R.Ranging(CM);     //read ultrasonic distance
      USFL = USF_L.Ranging(CM);
      USBR = USB_R.Ranging(CM);
      USBL = USB_L.Ranging(CM);
      
      Serial.print("FR=");
      Serial.print(USFR);       
      
      Serial.print("\t FL=");
      Serial.print(USFL); 
            
      Serial.print("\t BR=");
      Serial.print(USBR);      
        
      Serial.print("\t BL=");
      Serial.println(USBL);      

     /* read ir line sensor */
      IRFR_c = digitalRead(IRFR);
      IRFL_c = digitalRead(IRFL);
      IRBR_c = digitalRead(IRBR);
      IRBL_c = digitalRead(IRBR);
      
       Serial.print("\t FR=");
      Serial.print(IRFR_c);
      
      Serial.print("\t FL=");
      Serial.print(IRFL_c);
      
      Serial.print("\t BR=");
      Serial.print(IRBR_c);
      
      Serial.print("\t BL=");
      Serial.print(IRBL_c);

      delay(50);
  
//    GoLeft(80); 
//    delay(200);
    Forward(160);
    delay(500);

//    if (IRFR == 0 || IRFL == 0)
//    {
//      Backward(spdPush);
//      delay(500);
//    }
//
//    else if (IRBR == 0 || IRBL == 0)
//    {
//      Forward(spdPush);
//      delay(500);
//    }
//
//    else {
//        //case 1
//        
//        }
//        else GoRight(spdRotate);
//    }

    fightppl();
}

void fightppl()
{
  if (USFR <= detectRange && USFL <= detectRange)
        {
          Forward(spdPush);
        }
        
        //case 2
        else if (USBR <= detectRange && USBL <= detectRange)
        {
          Backward(spdPush);
        }

        //case 3
        else if (USFL <= detectRange && USFR > detectRange)
        {
            if (USFR <= detectRange && USFL <= detectRange)
          {
            Forward(spdPush);
          }
            else if (USBR <= detectRange && USBL <= detectRange)
          {
            Backward(spdPush);
          }
          else GoLeft(spdRotate);
        }
        
        //case 4
        else if (USFL > detectRange && USFR <= detectRange)
        {
            if (USFR <= detectRange && USFL <= detectRange)
          {
            Forward(spdPush);
          }
            else if (USBR <= detectRange && USBL <= detectRange)
          {
            Backward(spdPush);
          }
          else GoRight(spdRotate);
        }
       
        //case 5
        else if (USBL <= detectRange && USBR > detectRange)
        {
            if (USFR <= detectRange && USFL <= detectRange)
          {
            Forward(spdPush);
          }
            else if (USBR <= detectRange && USBL <= detectRange)
          {
            Backward(spdPush);
          }
          else GoRight(spdRotate);
        }
        
        //case 6
        else if (USBL > detectRange && USBR <= detectRange)
        {
            if (USFR <= detectRange && USFL <= detectRange)
          {
            Forward(spdPush);
          }
            else if (USBR <= detectRange && USBL <= detectRange)
          {
            Backward(spdPush);
          }
          else GoLeft(spdRotate);
        }
}
