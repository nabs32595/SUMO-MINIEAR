// Motor Driver Right 
const int RPWM_R=9;
const int LPWM_R=10;

// Motor Driver Left 
const int RPWM_L=3;
const int LPWM_L=2;

int spd = 30;

void setup()
{ 
  Serial.begin(57600);
   
  // Set the motor PWM pins as an output. 
  pinMode(RPWM_R, OUTPUT); 
  pinMode(LPWM_R, OUTPUT);
  pinMode(RPWM_L, OUTPUT);
  pinMode(LPWM_L, OUTPUT);
   
 //pin 9 and 10
 //TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
 TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  
 //pin 3 and 11
 //TCCR2B = TCCR2B & B11111000 | B00000001; // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
 TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

}

void loop() 
{
  Serial.println("start motor testing");
  delay(1000);
  
  Serial.println("backward");
  MoveR(spd,0); 
  delay(1000);
  
  Serial.println("forward");
  MoveR(0,spd);
  delay(1000);
  
//  Serial.println("left");
//  MoveLR(spd,0); 
//  delay(1000);
//  
//  Serial.println("right");
//  MoveLR(0,spd);  
//  delay(1000);
//  
//  Serial.println("stop for 3s");
//  MoveFB(0,0);
//  MoveLR(0,0);
//  delay(3000);
}

void MoveR(int S_LPWM_R, int S_RPWM_R)
{
  analogWrite (LPWM_R,S_LPWM_R);  
  analogWrite (RPWM_R,S_RPWM_R);  
}
void MoveL(int S_LPWM_L, int S_RPWM_L)
{
  analogWrite (LPWM_L,S_LPWM_L);   
  analogWrite (RPWM_L,S_RPWM_L);    
  
}
