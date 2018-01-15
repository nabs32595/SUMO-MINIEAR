/* 
 * Created by Loo Chuan Yin xD
 * 
 *************************************************************
 * Take note that all the Enable "EN" pin is connected to 5V.
 * Because the ENABLE PINS is always "ON" for this case.  
 * This is also to simplify the program. 
 * Thus, u will only see PWM pins assign as outputs.  
 */


#include <PS2X_lib.h>  //for v1.6
//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

/*
 * \ * * * | * * * | * * * /
 * \DAT,CMD,NC | GND,3.3V,SEL | CLK,NC,NC/ 
 */
 
// set pins connected to PS2 controller:
#define PS2_DAT        A0     
#define PS2_CMD        A1  
#define PS2_SEL        A2 
#define PS2_CLK        A3  

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

 

//++++++++++++++++++++++++++++++++++++++++++
int ToZero = 117; // tolerances for PS2 joystick
int ToTwoFF = 138; // tolerances for PS2 joystick

int NormalSpeed = 170;
int MaxSpeed = 250;
int OneSpd;

int SForward, SBackward, SLeft, SRight;
int SFWLeft, SBWLeft, SFWRight, SBWRight;
int SRotLeft, SRotRight, SRLeft, SRRight;

int SComBackRight, SComBackLeft, SComFrontRight, SComFrontLeft;

//++++++++++++++++++++++++++++++++++++++++++

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
  
  readPS2();
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
}

void loop() 
{
  if(error == 1) //skip loop if no controller found
    return; 
  else { 
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    DefinePS2Input();
    SpeedControl();
    JoyControl();
//    TestMotor();

  }
  delay(10); 
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
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 1);

  analogWrite(EFL, SForward);
  analogWrite(EFR, SForward);
  analogWrite(EBL, SForward);
  analogWrite(EBR, SForward);
}

void Backward(int SBackward)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 0);

  analogWrite(EFL, SBackward);
  analogWrite(EFR, SBackward);
  analogWrite(EBL, SBackward);
  analogWrite(EBR, SBackward);
}

void GoLeft(int SLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);

  analogWrite(EFL, SLeft);
  analogWrite(EFR, SLeft);
  analogWrite(EBL, SLeft);
  analogWrite(EBR, SLeft);
}
void GoRight(int SRight)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);

  analogWrite(EFL, SRight);
  analogWrite(EFR, SRight);
  analogWrite(EBL, SRight);
  analogWrite(EBR, SRight);
}

void FWRight(int SFWRight)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);

  analogWrite(EFL, SFWRight);
  analogWrite(EFR, 0);
  analogWrite(EBL, 0);
  analogWrite(EBR, SFWRight);
 
}
void BWRight(int SBWRight)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);

  analogWrite(EFL, 0);
  analogWrite(EFR, SBWRight);
  analogWrite(EBL, SBWRight);
  analogWrite(EBR, 0); 
}

void FWLeft(int SFWLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);

  analogWrite(EFL, 0);
  analogWrite(EFR, SFWLeft);
  analogWrite(EBL, SFWLeft);
  analogWrite(EBR, 0);
 }
 
void BWLeft(int SBWLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);

  analogWrite(EFL, SBWLeft);
  analogWrite(EFR, 0);
  analogWrite(EBL, 0);
  analogWrite(EBR, SBWLeft);
}

void RotateLeft(int SRotLeft)
{
  digitalWrite (FL1, 0);
  digitalWrite (FR1, 1);   
  digitalWrite (BL1, 0);
  digitalWrite (BR1, 1);

       
  analogWrite(EFL, SRotLeft);
  analogWrite(EFR, SRotLeft);
  analogWrite(EBL, SRotLeft);
  analogWrite(EBR, SRotLeft);
}

void RotateRight(int SRotRight)
{
  digitalWrite (FL1, 1);
  digitalWrite (FR1, 0);   
  digitalWrite (BL1, 1);
  digitalWrite (BR1, 0);

      
  analogWrite(EFL, SRotRight);
  analogWrite(EFR, SRotRight);
  analogWrite(EBL, SRotRight);
  analogWrite(EBR, SRotRight);
}


//-------------- Functions to define the joy stick --------------
/*    
     Left JoyStick (LY,LX)   |   Right JoyStick (RY,RX)
                             |
            (LY)             |          (RY)
             0               |           0
             |               |           |
             |               |           |
      0 --- 128 --- 255(LX)  |    0 --- 128 --- 255(RX)
             |               |           |
             |               |           |
            255              |          255
                             |
*/
void SpeedControl()
{
  if (L2){
    OneSpd = MaxSpeed;
  }
  else{
  OneSpd = NormalSpeed;
  }
}


void JoyControl()
{
  if(Start) Stop();
  else{
//------------------ To Control Forward and Backward --------------------------
  if(RY < ToZero && RX >= ToZero && RX <= ToTwoFF){
    Forward(OneSpd);
  }
  else if (RY > ToTwoFF && RX >= ToZero && RX <= ToTwoFF){
    Backward(OneSpd);
  }
  //------------------ To Control Left and Right --------------------------
    else if (RX < ToZero && RY >=ToZero && RY <= ToTwoFF){
      GoLeft(OneSpd);
    }
    else if (RX > ToTwoFF && RY >=ToZero && RY <= ToTwoFF){
      GoRight(OneSpd);
    }
  //------------------ Combine --------------------------
    else if (RY < ToZero && RX > ToTwoFF){    
      FWRight(OneSpd);
    }
    else if (RY > ToTwoFF && RX < ToZero){    
      BWLeft(OneSpd);
    }
    else if (RY < ToZero && RX < ToZero){     
      FWLeft(OneSpd);
    }
    else if (RY > ToTwoFF && RX > ToTwoFF){    
      BWRight(OneSpd);
    } 
    
    else if (LX < ToZero){     
      RotateLeft(OneSpd);
    }
    else if (LX > ToTwoFF){    
      RotateRight(OneSpd);
    }
    
    else Stop();
  }
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

void TestMotor()
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
