/* 
 *  Created by bRotheR yUn ^_^
 */

#include <PS2X_lib.h> 
//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.


/*
 * \ * * * | * * * | * * * /
 * \DAT,CMD,NC | GND,3.3V,SEL | CLK,NC,NC/ 
 */


// set pins connected to PS2 controller:
#define PS2_DAT        A0     // green
#define PS2_CMD        A1     // blue
#define PS2_SEL        A2     // chocolate (Attention pin)
#define PS2_CLK        A3     // orange


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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int ToZero = 126; // tolerances for PS2 joystick
int ToTwoFF = 129; // tolerances for PS2 joystick

int NormalSpeed = 200;
int MaxSpeed = 255;
int OneSpd;

int SForward, SBackward, SLeft, SRight;
int SFWLeft, SBWLeft, SFWRight, SBWRight;
int SRotLeft, SRotRight, SRLeft, SRRight;

int SComBackRight, SComBackLeft, SComFrontRight, SComFrontLeft;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//MOTOR DRIVER up - right
const int RPWM1 = 4; //green
const int LPWM1 = 5; //blue

//Motor Driver bottom - left
const int RPWM2 = 3;  //silver
const int LPWM2 = 2;  //purple


/******************************************************************************/
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

   readPS2();
   delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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


//--------------------------------------------movement-------------------------------------------------//

/*[digitalWrite/analogWrite(vin,1/0/speed)] untuk motor*/

void Stop()
{
  Move(0,0,0,0);
}

void Forward(int s_front)
{
  Move(0,s_front,s_front,0);
}

void Backward(int s_Backward)
{
  Move (s_Backward,0,0,s_Backward);
}

void GoRight (int s_right)
{
  Move(s_right,0,s_right,0);
}

void GoLeft (int s_left)
{
  Move(0,s_left,0,s_left);
}


//--------------------------------------------------------------------------------------------//

void Move(int S_RPWM1, int S_LPWM1, int S_RPWM2, int S_LPWM2)
{
  analogWrite (LPWM1,S_LPWM1);  
  analogWrite (RPWM1,S_RPWM1);  
  analogWrite (LPWM2,S_LPWM2);   
  analogWrite (RPWM2,S_RPWM2);   
}

//-----------------------------speed-----------------------------------------------------//

void SpeedControl()
{
  if (R2){
    OneSpd = MaxSpeed;
  }
  else{
  OneSpd = NormalSpeed;
  }
}



//-------------------- Functions to define the joy stick ------------------------------
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
       Move(0,SComFrontLeft,SComFrontLeft,0);
    }
    else if (RY > ToTwoFF && RX < ToZero){    
       Move(0,SComFrontRight,0,SComFrontRight);
    }  
    else if (RY < ToZero && RX < ToZero){     
       Move(SComBackLeft,0,SComBackLeft,0);
    }
    else if (RY > ToTwoFF && RX > ToTwoFF){    
      Move(SComBackRight,0,0,SComBackRight);
    }
    
    else Stop();
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
    Stop ();
    delay(1000);
    
    /*
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
    */
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
