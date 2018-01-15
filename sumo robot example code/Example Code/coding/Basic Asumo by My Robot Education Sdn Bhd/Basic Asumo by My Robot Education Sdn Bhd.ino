#include <NewPing.h>

NewPing sonar1(A2,A3,120); // NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
NewPing sonar2(2,3,120);

int value1=0;
int value2=0;
int value=0;
//Motor Pin
int MR1= 5;
int MR2= 6;
int ML1= 9;
int ML2 =10; 

int line_l=0;
int line_r=0;
int found=0;

void setup()
{
  pinMode(A4, INPUT);//sense line L
  pinMode(A5, INPUT);//sense line R when black =1, when white =0
  pinMode(ML1, OUTPUT);   // sets the pin as output
  pinMode(ML2, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT); 
  robotstop();
}

void robotstop()
{
    analogWrite(MR1,0);
    analogWrite(MR2,0); 
    analogWrite(ML1,0);
    analogWrite(ML2,0); 
}

void ir_find() //find opponent
{
  while (found==0)
  {
    analogWrite(MR1,100);
    analogWrite(MR2,0); 
    analogWrite(ML1,0);
    analogWrite(ML2,100); 
    value1=sonar1.ping_cm(); 
    value2=sonar2.ping_cm(); 
    delay(50);
   if ((value1>0)||(value2>0))
    {
    robotstop();
    delay(10);
    found=1;
    }
   line_l=digitalRead(A4);
   line_r=digitalRead(A5);  
   if ((line_l==LOW)||(line_r==LOW)) //if any sensor sense white line
    {
      robotstop();
      delay(10);
      found=1;
    }
  }
}



void fight() //When found opponent
{
  value1=sonar1.ping_cm(); //double check opponent
  value2=sonar2.ping_cm(); 
  delay(50);
  if ((value1>0)||(value2>0))
  {
        value=value1-value2;
        if (value<0)
        {
        analogWrite(MR1,220);
        analogWrite(MR2,0); 
        analogWrite(ML1,220-value);
        analogWrite(ML2,0); 
        }
        else
        {
        analogWrite(MR1,220+value);
        analogWrite(MR2,0); 
        analogWrite(ML1,220);
        analogWrite(ML2,0); 
         }
        delay(10);
        found=1;  
     }
    else 
    {
         found=0; 
    }
}

void sense_floor_black()
{
  line_l=digitalRead(A4);
  line_r=digitalRead(A5);  
  if ((line_l==HIGH)&&(line_r==HIGH))//all black
  {//ok, can find opponent / hit opponent
      if (found==0)//search
      {
        ir_find();
      }
      else//found
      {
        fight();
      }
    }
   else if ((line_l==LOW)&&(line_r==LOW))//ALL WHITE
   {
    analogWrite(MR1,0);
    analogWrite(MR2,250); 
    analogWrite(ML1,0);
    analogWrite(ML2,250);
    delay(500);
    robotstop();
   }
   else if (line_l==LOW)//L=white, turn right
   {
    analogWrite(MR1,0);
    analogWrite(MR2,250); 
    analogWrite(ML1,0);
    analogWrite(ML2,250);
    delay(300);
    analogWrite(MR1,0);
    analogWrite(MR2,250); 
    analogWrite(ML1,250);
    analogWrite(ML2,0);
    delay(200);
    robotstop();
   }
   else 
   {
    analogWrite(MR1,0);
    analogWrite(MR2,250); 
    analogWrite(ML1,0);
    analogWrite(ML2,250);
    delay(300);
    analogWrite(MR1,250);
    analogWrite(MR2,0); 
    analogWrite(ML1,0);
    analogWrite(ML2,250);
    delay(200);
    robotstop();
   }
}

void loop() 
{
sense_floor_black();
}
