
//MOTOR DRIVER up - left
const int RPWM1 = 3;
const int LPWM1 = 2;

//Motor Driver bottom - right
const int RPWM2 = 5;  //pin5
const int LPWM2 = 4;  //pin4


void setup ()

{
  Serial.begin(57600);
   
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


//--------------------------------------------------------------------------------------------//

void Move(int S_RPWM1, int S_LPWM1, int S_RPWM2, int S_LPWM2)
{
  analogWrite (LPWM1,S_LPWM1);  
  analogWrite (RPWM1,S_RPWM1);  
  analogWrite (LPWM2,S_LPWM2);   
  analogWrite (RPWM2,S_RPWM2);    
}

void Stop()
{
  Move(0,0,0,0);
}

void Forward(int s_front)
{
  Move (s_front, 0,s_front ,0);
}

void Backward(int s_Backward)
{
  Move (0,s_Backward,0,s_Backward);
}

void GoRight (int s_right)
{
  Move (0,0,0,s_right);
  //Move(0,0,0,s_right);
}

void GoLeft (int s_left)
{
  Move(0,s_left,0,s_left);
  //Move(0,0,s_left,0);
}



int speed = 180;

void loop()
{
  //  Forward(speed);
  //delay(1000);
    //Backward(speed);
    //delay(1000);
  GoLeft(speed);
    delay(1000);
//    GoRight(speed);
//    delay(1000);
//    Stop();
//    delay(1000);
}


