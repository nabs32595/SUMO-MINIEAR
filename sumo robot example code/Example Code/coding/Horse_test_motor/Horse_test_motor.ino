//Assign pins for Motor (Front Left)
int EFL = 3;  
int FL1 = 2; 

//Assign pins for Motor (Front Right)
int EFR = 5;  
int FR1 = 4; 

//Assign pins for Motor (Back Left)
int EBL = 6;  
int BL1 = 7;

//Assign pins for Motor (Back Right)
int EBR = 9;  
int BR1 = 8; 

int SForward, SBackward, SLeft, SRight;
int SFWLeft, SBWLeft, SFWRight, SBWRight;
int SRotLeft, SRotRight;

void setup()
{ 
  Serial.begin(57600);
  
  pinMode(EFL, OUTPUT);
  pinMode(FL1, OUTPUT);
  
  pinMode(EFR, OUTPUT);
  pinMode(FR1, OUTPUT);
  
  pinMode(EBL, OUTPUT);
  pinMode(BL1, OUTPUT);
  
  pinMode(EBR, OUTPUT);
  pinMode(BR1, OUTPUT);
  
}

void loop() 
{
  RotateLeft(100);
    delay(1000);
    RotateRight(100);
    delay(1000);
  Stop();
  delay(3000);
    //TestMotor();
}

//-------------- Functions to define the movement --------------
void Stop(){
  analogWrite(EFL, 0);
  analogWrite(EFR, 0);
  analogWrite(EBL, 0);
  analogWrite(EBR, 0);
}

void Forward(int SForward)
{
  digitalWrite (FL1, 1);
  digitalWrite (BL1, 1);
  digitalWrite (FR1, 1);
  digitalWrite (BR1, 1);
     
  analogWrite(EFL, SForward);
  analogWrite(EFR, SForward);
  analogWrite(EBL, SForward);
  analogWrite(EBR, SForward);
}

void Backward(int SBackward)
{
  digitalWrite (FL1, 0);
  digitalWrite (BL1, 0);
  digitalWrite (FR1, 0);
  digitalWrite (BR1, 0);
      
  analogWrite(EFL, SBackward);
  analogWrite(EFR, SBackward);
  analogWrite(EBL, SBackward);
  analogWrite(EBR, SBackward);
}

void GoLeft(int SLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (BL1, 1);
  digitalWrite (FR1, 1);
  digitalWrite (BR1, 0);
      
  analogWrite(EFL, SLeft);
  analogWrite(EFR, SLeft);
  analogWrite(EBL, SLeft);
  analogWrite(EBR, SLeft);
}

void GoRight(int SRight)
{
  digitalWrite (FL1, 1);
  digitalWrite (BL1, 0);
  digitalWrite (FR1, 0);
  digitalWrite (BR1, 1);
      
  analogWrite(EFL, SRight);
  analogWrite(EFR, SRight);
  analogWrite(EBL, SRight);
  analogWrite(EBR, SRight);
}

void FWLeft(int SFWLeft)
{
  digitalWrite (FL1, 0);  
  digitalWrite (BL1, 1);
  digitalWrite (FR1, 1);  
  digitalWrite (BR1, 0);
      
  analogWrite(EFL, 0);
  analogWrite(EBL, SFWLeft);
  analogWrite(EFR, SFWLeft);
  analogWrite(EBR, 0);
}

void FWRight(int SFWRight)
{
  digitalWrite (FL1, 1);  
  digitalWrite (BL1, 0);
  digitalWrite (FR1, 0);  
  digitalWrite (BR1, 1);
      
  analogWrite(EFL, SFWRight);
  analogWrite(EBL, 0);
  analogWrite(EFR, 0);
  analogWrite(EBR, SFWRight);
}

void BWLeft(int SBWLeft)
{
  digitalWrite (FL1, 0);   
  digitalWrite (BL1, 1);
  digitalWrite (FR1, 1);  
  digitalWrite (BR1, 0);
      
  analogWrite(EFL, SBWLeft);
  analogWrite(EBL, 0);
  analogWrite(EFR, 0);
  analogWrite(EBR, SBWLeft);
}

void BWRight(int SBWRight)
{
  digitalWrite (FL1, 1);   
  digitalWrite (BL1, 0);
  digitalWrite (FR1, 0);   
  digitalWrite (BR1, 1);
  
  analogWrite(EFL, 0);
  analogWrite(EBL, SBWRight);
  analogWrite(EFR, SBWRight);
  analogWrite(EBR, 0);    
}

void RotateLeft(int SRotLeft)
{
  digitalWrite (FL1, 0);  
  digitalWrite (BL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BR1, 1);
      
  analogWrite(EFL, SRotLeft);
  analogWrite(EFR, SRotLeft);
  analogWrite(EBL, SRotLeft);
  analogWrite(EBR, SRotLeft);
}

void RotateRight(int SRotRight)
{
  digitalWrite (FL1, 1);  
  digitalWrite (BL1, 1);
  digitalWrite (FR1, 0);  
  digitalWrite (BR1, 0);
      
  analogWrite(EFL, SRotRight);
  analogWrite(EFR, SRotRight);
  analogWrite(EBL, SRotRight);
  analogWrite(EBR, SRotRight);
}

void TestMotor()
{
  int i = 130;

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
