/*declare ir line sensor*/

int IRFR = A2; //HIJAU
int IRFL = A1; //KUNING
int IRBR = A3; //BIRU
int IRBL = A0; //OREN

//MOTOR DRIVER right
const int RPWM1 = 10;
const int LPWM1 = 9;

//Motor Driver left
const int RPWM2 = 3;
const int LPWM2 = 11;

int IRFRVal, IRFLVal, IRBRVal, IRBLVal;

/*include dr library so it know ultrasonic*/

#include "Ultrasonic.h"

/*declare what pin 4 which ultrasonic (trigger,echo)*/

Ultrasonic US_F (6,7);
Ultrasonic US_B (12,13);

/*declare ultrasonic*/

int USF;
int USB;

void setup ()

{

  Serial.begin(9600);
   
   pinMode(RPWM1,OUTPUT);
   pinMode(LPWM1,OUTPUT);
 
   pinMode(RPWM2,OUTPUT);
   pinMode(LPWM2,OUTPUT);

     //pin 9 and 10
 TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
 //TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  
 //pin 3 and 11
 TCCR2B = TCCR2B & B11111000 | B00000001; // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
 //TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
}

//--------------------------------------------movement-------------------------------------------------//

/*[digitalWrite/analogWrite(vin,1/0/speed)] untuk motor*/

void Stop()
{
  Move(0,0,0,0);
}

void GoLeft (int s_right)
{
  Move(s_right,0,0,s_right);
}

void GoRight (int s_left)
{
  Move(0,s_left,s_left,0);
}

void Reverse(int s_reverse)
{
  Move (0,s_reverse,0,s_reverse);
}

void Forward(int s_front)
{
  Move(s_front, 0, s_front, 0);
}

void Move(int S_RPWM1, int S_LPWM1, int S_RPWM2, int S_LPWM2)

{

  analogWrite(RPWM1,S_RPWM1);
  analogWrite(LPWM1,S_LPWM1);
  
  analogWrite(RPWM2,S_RPWM2);
  analogWrite(LPWM2,S_LPWM2);

}

void loop()

{
    IRreading();
    /*ultrasonic*/

   

    if (IRFRVal == 1 && IRFLVal == 1 && IRBRVal == 1 && IRBLVal == 1)
    {
      GoLeft(200);
      if (USF <= 50)
     {
      Forward (200);
     }
     else if (USB <= 50)
     {
      Reverse (200);
     }
    }

    if (IRFRVal == 0 || IRFLVal == 0)
    {
      Reverse (150);
      delay(500);
    }

    else if (IRBRVal == 0 || IRBLVal == 0)
    {
      Forward (150);
      delay(500);
    }
    
  
}

void IRreading()
{
      IRFRVal = digitalRead(IRFR);
    Serial.print("IRFR=");
    Serial.print(IRFRVal);
    
    IRFLVal = digitalRead(IRFL);
    Serial.print("\t IRFL=");
    Serial.print(IRFLVal);
    
    IRBRVal = digitalRead(IRBR);
    Serial.print("\t IRBR=");
    Serial.print(IRBRVal);
    
    IRBLVal = digitalRead(IRBL);
    Serial.print("\t IRBL=");
    Serial.print(IRBLVal);

     USF = US_F.Ranging(CM);  //formula read ultrasonic range
    USB = US_B.Ranging(CM);

    Serial.print("\t USF=");
    Serial.print (USF);

    Serial.print("\t USB=");
    Serial.println (USB);
}
