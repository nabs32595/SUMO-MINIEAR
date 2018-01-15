#include "Ultrasonic.h"
Ultrasonic USRight(22, 23); //Trigger = pin 22, Echo =pin 23
Ultrasonic USMid(24,25);
Ultrasonic USLeft(26,27);

//Assign reading integer for ultrasonic
int USR;
int USM;
int USL;

//Assign pins for Motor 1 (Right)
int Ea = 5;  //ENA
int M1a = 51; //IN2
int M1b = 50; //IN1

//Assign pins for Motor 2 (Left)
int Eb = 6;  //ENB
int M2a = 53; //IN4
int M2b = 52; //IN3

//Assign pins for Fan
int Ec = 7;
int M3a = 48;
int M3b = 49;

//Pin for Flame sensor power Supply
int Vin = 13;
int sensorRight;
int sensorLeft;

//To control motor speed
float r = 0.55;
float l = 0.50;
float n = 0.50;

void setup()
{
  Serial.begin(9600);
  pinMode(Ea, OUTPUT);
  pinMode(M1a, OUTPUT);
  pinMode(M1b, OUTPUT);
  pinMode(Eb, OUTPUT);
  pinMode(M2a, OUTPUT);
  pinMode(M2b, OUTPUT);
  pinMode(Ec, OUTPUT);
  pinMode(M3a,OUTPUT);
  pinMode(M3b,OUTPUT);
  pinMode(Vin,OUTPUT);
  digitalWrite(Vin,HIGH);

}

void loop()
{
  noInterrupts();
  {
    Serial.print(USR);
    Serial.print("\t");
    Serial.print(USM);
    Serial.print("\t");
    Serial.print(USL);
    Serial.print("\t");
  
    Serial.print(sensorRight);
    Serial.print("\t");
    Serial.println(sensorLeft);
  
  
    USR = USRight.Ranging(CM);  
    USM = USMid.Ranging(CM);
    USL = USLeft.Ranging(CM);
  
   sensorRight = analogRead(A0);
    delay (5);
    sensorLeft = analogRead(A1);
    delay(5);
  }
  interrupts();
  {
   //Case1
   if(USM<=13 && sensorRight<800 && sensorLeft<800)
   {
     Stop();
     delay(1000);
     Fan(255);
     delay(1000);
   
   //Case1extra
   if(USM<=13 && USL<=15 && USR>11 && sensorRight>800 && sensorLeft>800)
   { 
     Fan(0);
     Stop();
     RotateRight(100);
     delay(750);
   }
   //Case1extra
   else if(USM<=14 && USL<=15 && USR<=15 && sensorRight>800 && sensorLeft>800)
   { 
     Fan(0);
     Stop();
     RotateRight(100);
     delay(1250);
   }
   //Case1extra
   else if(USM<=14 && USL<8 && USR<=15 && sensorRight>800 && sensorLeft>800)
   { 
     Fan(0);
     Stop();
     RotateLeft(80);
     delay(660);
   }
 
 }
   
      
   
   //Case2
   else if(USL>5 && USL<=13&& USM>15 && USR>5 && USR<=13 && sensorRight>800 && sensorLeft>800)
   { 
       Fan(0);
       Forward(70);
   }
   
   //Case3
   else if(USL>8 && USM<=15 && USR>5 && USR<=13 && sensorRight>800 && sensorLeft>800)
   {
       Fan(0);
       RotateLeft(80);
       delay(350);
       Forward(70);
       delay(500);
   }
   
   //Case4
   else if(USL>5 && USL<=3 && USM<=15 && USR>13 && sensorRight>800 && sensorLeft>800)
   {
     Fan(0);
     RotateRight(100);
     delay(750);
     Forward(70);
     delay(500);
   }
   
   //Case5
   else if(USL<=5 && USM>15 && USR>13 && sensorRight>800 && sensorLeft>800)
   {
     AdjRight(70);
     delay(350);
     Fan(0);
   }
   
   //Case6
   else if(USL>13 && USM>15 && USR<5 && sensorRight>800 && sensorLeft>800)
   {
     AdjLeft(70);
     delay(350);
     Fan(0);
   }
   
   //Case7
   else if(USL>13 && USM>15 && USR>13 && sensorRight>800 && sensorLeft>800)
   {
     RotateLeft(100);
     delay(500);
     Forward(70);
     delay(1000);
     Fan(0);
   }
   
   //Case8
   else if(USM<=14 && sensorRight>800 && sensorLeft<800)
   {
     Stop();
     delay(1000);
     RotateLeft(80);
     delay(500);
     Fan(0);
   }
   
     
   //Case9
   else if(USM<=14 && sensorRight<800 && sensorLeft>800)
   {
     Stop();
     delay(1000);
     RotateRight(100);
     delay(200);
   }
   
   //Case10
   else if(USL<=8 && USM<=14 && USR<=13 && sensorRight>800 && sensorLeft>800)
   {
     RotateRight(100);
     delay(1250);
     Fan(0);
   }
   
   //Case11
   else if(USL>5 && USL<=14 && USM>15 && USR>10 && sensorRight>800 && sensorLeft>800)
   {
     Forward(70);
     Fan(0);
   }
   
   //Case12
   else if(USL<=5 && USM>15 && USR>10 && sensorRight>800 && sensorLeft>800)
   {
     AdjLeft(70);
     delay(500);
     Fan(0);
   }
   
   //Case 13
   else if(USL>15 && USM>15 && USR>10)
   {
     AdjRight(70);
     delay(500);
   }
   
   //SpecialCase 
   else
   {
     Forward(70);
     Fan(0);
   }
  }//delay(500);
}

  
 


//++++++++++++++++++++++++++FUNCTIONS++++++++++++++++++++++++++++++++
void Stop()
{
  analogWrite(Ea,0);
  analogWrite(Eb,0);
}

void Forward(int Speed)
{
  digitalWrite (M1a, 0);
  digitalWrite (M1b, 1);
  digitalWrite (M2a, 1);
  digitalWrite (M2b, 0);
  
  analogWrite(Ea, Speed*n);
  analogWrite(Eb, Speed);
}

void AdjRight(int Speed)
{
  digitalWrite (M1a, 0);
  digitalWrite (M1b, 1);
  digitalWrite (M2a, 1);
  digitalWrite (M2b, 0);
  
  analogWrite(Ea, Speed);
  analogWrite(Eb, Speed*r);
}

void AdjLeft(int Speed)
{
  digitalWrite (M1a, 0);
  digitalWrite (M1b, 1);
  digitalWrite (M2a, 1);
  digitalWrite (M2b, 0);
  
  analogWrite(Ea, Speed*l);
  analogWrite(Eb, Speed);
}

void Backward(int Speed)
{
  digitalWrite (M1a, 1);
  digitalWrite (M1b, 0);
  digitalWrite (M2a, 0);
  digitalWrite (M2b, 1);
  
  analogWrite(Ea, Speed);
  analogWrite(Eb, Speed);
}

void RotateLeft(int Speed)
{
  digitalWrite (M1a, 1);
  digitalWrite (M1b, 0);
  digitalWrite (M2a, 1);
  digitalWrite (M2b, 0);
  
  analogWrite(Ea, Speed);
  analogWrite(Eb, Speed);
}

void RotateRight(int Speed)
{
  digitalWrite (M1a, 0);
  digitalWrite (M1b, 1);
  digitalWrite (M2a, 0);
  digitalWrite (M2b, 1);
  
  analogWrite(Ea, Speed);
  analogWrite(Eb, Speed);
}

void Fan (int Speed)
{
  digitalWrite (M3a,1);
  digitalWrite (M3b,0);
  
  analogWrite(Ec, Speed);
}
