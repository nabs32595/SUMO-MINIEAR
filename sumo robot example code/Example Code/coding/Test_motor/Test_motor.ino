/*
 
 //MOTOR DRIVER 1 FRONT

//Assign pins for Motor 
int EFL = 2; //PWM1 pin grey
int FL1 = 22; //DIR1 pin purple

//Assign pins for Motor  
int EFR = 3;  //PWM2 pin black
int FR1 = 24;  //DIR2 pin white  

//MOTOR DRIVER 2 BACK

//Assign pins for Motor 
int EBR = 5;  //PWM2 pin white
int BR1 = 28;  //DIR2 pin black

//Assign pins for Motor  
int EBL = 4;   //PWM1 pin brown
int BL1 = 26;   //DIR1 pin red 


void setup()
{
 
Serial.begin(57600);
pinMode(EFL, OUTPUT);
pinMode(FL1, OUTPUT);
pinMode(EFR, OUTPUT);
pinMode(FR1, OUTPUT);
pinMode(EBR, OUTPUT);
pinMode(BR1, OUTPUT);
pinMode(EBL, OUTPUT);
pinMode(BL1, OUTPUT);
}


//-------------- Functions to define the movement --------------
void Stop()
{
  analogWrite(EFL, 0);
  analogWrite(EFR, 0);
  analogWrite(EBL, 0);
  analogWrite(EBR, 0);
}

void Forward(int SForward)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);
}

void Backward(int SBackward)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);
}

  void GoLeft(int SLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);
}

  void GoRight(int SRight)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);
}

  void FWRight(int SFWRight)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);
}

void BWRight(int SBWRight)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 0);
}

void FWLeft(int SFWLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);
}

void BWLeft(int SBWLeft)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 0);
}

void RotateLeft(int SRotLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);
}

void RotateRight(int SRotRight)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);
}




//TEST

void testing()
{
  int i = 200;

    Forward (i);
    delay(1000);
    Backward (i);
    delay(1000);
    GoLeft(i);
    delay(1000);
    GoRight(i);
    delay(1000);
    
    FWRight(i);
    delay(1000);
    FWLeft(i);
    delay(1000);
    BWRight(i);
    delay(1000);
    BWLeft(i);
    delay(1000);
    
    RotateLeft(i);
    delay(1000);
    RotateRight(i);
    delay(1000);
    
    Stop();
    delay(1000);
}

*/

//MOTOR DRIVER 1 FRONT(UP)

//Assign pins for Motor 
int EFL = 6; //PWM1 pin grey
int FL = 7; //DIR1 pin purple

//Assign pins for Motor  
int EFR = 5;  //PWM2 pin black
int FR = 4;  //DIR2 pin white  

//MOTOR DRIVER 2 BACK (DOWN)

//Assign pins for Motor 
int EBR = 11;  //PWM1 pin white
int BR = 13;  //DIR1 pin black

//Assign pins for Motor  
int EBL = 10;   //PWM2 pin brown
int BL = 12;   //DIR2 pin red 


void Stop()
{
  analogWrite(EFL, 0);
  analogWrite(EFR, 0);
  analogWrite(EBL, 0);
  analogWrite(EBR, 0);
}

void Forward(int SForward)
{
  analogWrite(EFL, SForward);
  analogWrite(EFR, SForward);
  analogWrite(EBL, SForward);
  analogWrite(EBR, SForward);

  
  digitalWrite (FL, 1);
  digitalWrite (FR, 1);   
  digitalWrite (BL, 1);
  digitalWrite (BR, 1);
}

void Backward(int SBackward)
{
  analogWrite(EFL, SBackward);
  analogWrite(EFR, SBackward);
  analogWrite(EBL, SBackward);
  analogWrite(EBR, SBackward);
  
  digitalWrite (FL, 0);
  digitalWrite (FR, 0);   
  digitalWrite (BL, 0);
  digitalWrite (BR, 0);
}

  void GoLeft(int SLeft)
{
  analogWrite(EFL, SLeft);
  analogWrite(EFR, SLeft);
  analogWrite(EBL, SLeft);
  analogWrite(EBR, SLeft);
  
  digitalWrite (FL, 1);
  digitalWrite (FR, 0);   
  digitalWrite (BL, 0);
  digitalWrite (BR, 1);
}

  void GoRight(int SRight)
{
  analogWrite(EFL, SRight);
  analogWrite(EFR, SRight);
  analogWrite(EBL, SRight);
  analogWrite(EBR, SRight);
  
  digitalWrite (FL, 0);
  digitalWrite (FR, 1);   
  digitalWrite (BL, 1);
  digitalWrite (BR, 0);
}

/*------------------------------------------------------------------------------*/
void setup()
{
  Serial.print(9600);
 
}

void loop()
{
 /* read ultrasonic */
      USFR = USF_R.Ranging(CM);     //read ultrasonic distance
      USFL = USF_L.Ranging(CM);
      USBR = USB_R.Ranging(CM);
      USBL = USB_L.Ranging(CM);
      
      Serial.println(USFR);         //send value to serial monitor
      Serial.print("\t");
      Serial.println(USFL);         //send value to serial monitor
      Serial.print("\t");
      Serial.println(USBR);         //send value to serial monitor
      Serial.print("\t");
      Serial.println(USBL);         //send value to serial monitor
      Serial.print("\t");

   /*  
  Forward (255);
  delay(1000);
  Backward(255);
  delay(1000);
  GoLeft(255);
  delay(1000);
  GoRight(255);
  delay(1000);
  */
  
  
}

