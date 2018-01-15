#include<Ultrasonic.h>

Ultrasonic USRight(9,8); //Trigger=Pin12, Echo=Pin13 
Ultrasonic USLeft(3,2);
Ultrasonic USFront(11,10);
Ultrasonic USBack(12,13);

//declare for Ultrasonic
int USR;  //declare for ultrasonic USRight
int USL;  //declare for ultrasonic USLeft
int USF; //declare for ultrasonic front USLeft
int USB; //declare for ultrasonic back USLeft

//Assign pins for Motor(Right)
int Dir1 = 8;  //pin 7 for Dir1
int PWM1 = 9;  //pin 6 for PWM1

//Assign pins for Motor (Left)
int Dir2 = 11; //pin 5 for Dir2 
int PWM2 = 10; //pin 4 for PWM2

int spdPush = 250;
int spdRotate = spdPush/2;
int detectRange = 50;



   //pin 9 and 10
 //TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
 TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  
 //pin 3 and 11
 //TCCR2B = TCCR2B & B11111000 | B00000001; // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
 //TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

}

void loop() 
{
  testing();
  
  //Sumo();
}

void Sumo()
{
  USreading();
  
  FightOperation();
  

}

void FightOperation()
{
  if (USF < detectRange && USB >= detectRange && USL >= detectRange && USR >= detectRange ) //case 1
  {
    Forward(spdPush);
  }
  
  else if (USL <detectRange && USF >= detectRange && USB >= detectRange && USR >= detectRange ) //case 2
  {
    if (USF < detectRange && USB >= detectRange && USL >= detectRange && USR >= detectRange ){
      Forward(spdPush);
    }
    else if (USB < detectRange && USF >= detectRange && USL >= detectRange && USR >= detectRange) {
      Backward(spdPush);
    }
    else RotateLeft(spdRotate);
  }
  
  else if (USR <detectRange && USF >= detectRange && USB >= detectRange && USL >= detectRange) //case 3
  {
    if (USF < detectRange && USB >= detectRange && USL >= detectRange && USR >= detectRange ){
      Forward(spdPush);
    }
    else if (USB < detectRange && USF >= detectRange && USL >= detectRange && USR >= detectRange){
      Backward(spdPush);
    }
    else RotateRight(spdRotate);
  }

  else if (USB < detectRange && USF >= detectRange && USL >= detectRange && USR >= detectRange) //case 1
  {
    Backward(spdPush);
  }
  
  else RotateRight(spdRotate);
}

void USreading()
{
  //read ultrasonic
      USR = USRight.Ranging(CM);  //read ultrasonic distance
      USL = USLeft.Ranging(CM);
      USF = USFront.Ranging(CM);
      USB = USBack.Ranging(CM);

      if (USR>399){ USR = 0; }
      if (USL>399){ USL = 0; }
      if (USF>399){ USF = 0; }
      if (USB>399){ USB = 0; }

  Serial.print("F=");
  Serial.print(USF);
  
  Serial.print("\t B=");
  Serial.print(USB);

  Serial.print("\t R=");
  Serial.print(USR);
  
  Serial.print("\t L=");
  Serial.println(USL);
}

void testing(void)
{
  int spd =80;
  Forward(spd);
  delay(1000);
  Backward(spd);
  delay(1000);
  RotateLeft(spd);
  delay(1000);
  RotateRight(spd);
  delay(1000);
  Stop();
  delay(1000);
}

void Stop()
{
  Move (0,0,0,0);
}

void Forward(int SForward){
  Move (1,1,SForward,SForward);
}

void Backward(int SBackward){
  Move (0,0,SBackward,SBackward);
}

void RotateLeft (int SRotLeft){
  Move (0,1,SRotLeft, SRotLeft);
}

void RotateRight (int SRotRight){
  Move (1,0, SRotRight, SRotRight);
}

void Move (byte Dir1state, byte Dir2state, int s_PWM1, int s_PWM2)
{
  digitalWrite(Dir1,Dir1state);
  digitalWrite(Dir2,Dir2state);

  analogWrite(PWM1,s_PWM1);
  analogWrite(PWM2,s_PWM2);
}
  
