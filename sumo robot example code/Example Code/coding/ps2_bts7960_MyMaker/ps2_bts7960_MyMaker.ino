#include <PS2X_lib.h> 

/*
 * \ * * * | * * * | * * * /
 * \DAT,CMD,NC | GND,3.3V,SEL | CLK,NC,NC/ */

#define PS2_DAT        A1     
#define PS2_CMD        A2  
#define PS2_SEL        A3  
#define PS2_CLK        A4  

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;
int LX,LY,RX,RY ; // to define variables for PS2 joystick
int Up, Down, Left, Right, Tri, Squ, Exx, Cir, Start, Select, L1, L2, L3, R1, R2, R3;

// Motor Driver Front Back (Big Motor)
const int RPWM_FB=10;
const int LPWM_FB=9;

const int FB_lEN = 4;
const int FB_rEN = 5;

// Motor Driver Left Right (Small Motor)
const int RPWM_LR=3;
const int LPWM_LR=11;

int SForward, SBackward, SLeft, SRight;
int SComBackRight, SComBackLeft, SComFrontRight, SComFrontLeft;

int ToZero = 126; // tolerances for PS2 joystick
int ToTwoFF = 129; // tolerances for PS2 joystick
int MaxSpeed = 255;
//###########################
void setup()
{ 
  Serial.begin(57600);
   
  // Set the motor PWM pins as an output. 
  pinMode(FB_lEN, OUTPUT);
  pinMode(FB_rEN, OUTPUT);
  pinMode(RPWM_FB, OUTPUT); 
  pinMode(LPWM_FB, OUTPUT);
  pinMode(RPWM_LR, OUTPUT);
  pinMode(LPWM_LR, OUTPUT);
  
   
 //pin 9 and 10
 //TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
 TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  
 //pin 3 and 11
 //TCCR2B = TCCR2B & B11111000 | B00000001; // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
 TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
 
 readPS2();
 delay(200);  //added delay to give wireless ps2 module some time to startup, before configuring it
}

void loop() 
{
  if(error == 1) //skip loop if no controller found
    return; 
  else { 
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    DefinePS2Input();
    ReadPS2AnalogVal();
   
    JoyControl();
  }
  delay(10);
}

//###################################################
void Move(int S_LPWM_FB, int S_RPWM_FB, int S_LPWM_LR, int S_RPWM_LR)
{
  analogWrite (LPWM_FB,S_LPWM_FB);  
  analogWrite (RPWM_FB,S_RPWM_FB);  
  analogWrite (LPWM_LR,S_LPWM_LR);   
  analogWrite (RPWM_LR,S_RPWM_LR);    
}

void Stop()
{
  Move(0,0,0,0);
  digitalWrite(FB_lEN, 1);
  digitalWrite(FB_rEN, 1);
}

void JoyControl()
{
  if(Start) Stop();
  else{
//------------------ To Control Forward and Backward --------------------------
    if(RY < ToZero && LX >=ToZero && LX <= ToTwoFF){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(0,SForward,0,0);
    }
    else if (RY > ToTwoFF && LX >=ToZero && LX <= ToTwoFF){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(SBackward,0,0,0);
    }
  //------------------ To Control Left and Right --------------------------
    else if (LX < ToZero && RY >=ToZero && RY <= ToTwoFF){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(0,0,SLeft,0); 
    }
    else if (LX > ToTwoFF && RY >=ToZero && RY <= ToTwoFF){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(0,0,0,SRight);
    }
  //------------------ Combine --------------------------
    else if (RY < ToZero && LX < ToZero){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(0,SComFrontLeft,SComFrontLeft,0);
    }
    else if (RY < ToZero && LX > ToTwoFF){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(0,SComFrontRight,0,SComFrontRight);
    }
    else if (RY > ToTwoFF && LX < ToZero){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(SComBackLeft,0,SComBackLeft,0);
    }
    else if (RY > ToTwoFF && LX > ToTwoFF){
      digitalWrite(FB_lEN, 1); digitalWrite(FB_rEN, 1);
      Move(SComBackRight,0,0,SComBackRight);
    }
    else Stop();
  }

}

void ReadPS2AnalogVal()
{
  int LXToZero = ps2x.Analog(PSS_LX);
  LXToZero = map(LXToZero, ToZero, 0, 0, MaxSpeed);
  if (LXToZero < 0) {
    LXToZero = 0;}
  SLeft = LXToZero ;
  Serial.print(SLeft); Serial.print("\t");
      
  int LXToTwoFF = ps2x.Analog(PSS_LX);
  LXToTwoFF = map(LXToTwoFF, ToTwoFF, 255, 0, MaxSpeed);
  if (LXToTwoFF < 0) {
    LXToTwoFF = 0;}
  SRight = LXToTwoFF ;
  Serial.print(SRight); Serial.print("\t");
    
  int RYToZero = ps2x.Analog(PSS_RY);
  RYToZero = map(RYToZero, ToZero, 0, 0, MaxSpeed);
  if (RYToZero < 0) {
    RYToZero = 0;}
  SForward = RYToZero ;
  Serial.print(SForward); Serial.print("\t");
    
  int RYToTwoFF = ps2x.Analog(PSS_RY);
  RYToTwoFF = map(RYToTwoFF, ToTwoFF, 255, 0, MaxSpeed);
  if (RYToTwoFF < 0) {
    RYToTwoFF = 0;}
  SBackward = RYToTwoFF ;
  Serial.print(SBackward); Serial.print("\t"); 
  
  SComBackRight = ((SBackward+SRight)/2);
  if (SComBackRight > 255){
    SComBackRight = MaxSpeed;
  }
  Serial.print(SComBackRight); Serial.print("\t");
  
  SComBackLeft = ((SBackward+SLeft)/2);
  if (SComBackLeft > 255){
    SComBackLeft = MaxSpeed;
  }
  Serial.print(SComBackLeft); Serial.print("\t");
  
  SComFrontRight = ((SForward+SRight)/2);
  if (SComFrontRight > 255){
    SComFrontRight = MaxSpeed;
  }
  Serial.print(SComFrontRight); Serial.print("\t");
  
  SComFrontLeft = ((SForward+SLeft)/2);
  if (SComFrontLeft > 255){
    SComFrontLeft = MaxSpeed;
  }
  Serial.print(SComFrontLeft); Serial.print("\t"); Serial.print("\n");
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void readPS2()
{
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
	if (pressures)
	  Serial.println("true ");
	else
	  Serial.println("false");
	Serial.print("rumble = ");
	if (rumble)
	  Serial.println("true)");
	else
	  Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
}

void DefinePS2Input()
{
    Up     = ps2x.Button(PSB_PAD_UP);
    Down   = ps2x.Button(PSB_PAD_DOWN);
    Left   = ps2x.Button(PSB_PAD_LEFT);
    Right  = ps2x.Button(PSB_PAD_RIGHT);
    Tri    = ps2x.Button(PSB_TRIANGLE);
    Squ    = ps2x.Button(PSB_SQUARE);
    Exx    = ps2x.Button(PSB_CROSS);
    Cir    = ps2x.Button(PSB_CIRCLE);
    Start  = ps2x.Button(PSB_START);
    Select = ps2x.Button(PSB_SELECT);
    L1     = ps2x.Button(PSB_L1);
    L2     = ps2x.Button(PSB_L2);
    L3     = ps2x.Button(PSB_L3);
    R1     = ps2x.Button(PSB_R1);
    R2     = ps2x.Button(PSB_R2);
    R3     = ps2x.Button(PSB_R3);
  
    LY = ps2x.Analog(PSS_LY);
    LX = ps2x.Analog(PSS_LX);
    RY = ps2x.Analog(PSS_RY);
    RX = ps2x.Analog(PSS_RX);
}

