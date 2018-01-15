// ---------------------------------------------------------
// This example code was used to successfully communicate
// with 15 ultrasonic sensors. You can adjust the number of
// sensors in your project by changing SONAR_NUM and the
// number of NewPing objects in the "sonar" array. You also
// need to change the pins for each sensor for the NewPing
// objects. Each sensor is pinged at 33ms intervals. So, one
// cycle of all sensors takes 495ms (33 * 15 = 495ms). The
// results are sent to the "oneSensorCycle" function which
// currently just displays the distance data. Your project
// would normally process the sensor results in this
// function (for example, decide if a robot needs to turn
// and call the turn function). Keep in mind this example is
// event-driven. Your complete sketch needs to be written so
// there's no "delay" commands and the loop() cycles at
// faster than a 33ms rate. If other processes take longer
// than 33ms, you'll need to increase PING_INTERVAL so it
// doesn't get behind.
// ---------------------------------------------------------
#include <NewPing.h>

#define SONAR_NUM     4 // Number or sensors.
#define MAX_DISTANCE 150 // Max distance in cm.
#define PING_INTERVAL 33 // Milliseconds between pings.

unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.

NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(13, 12, MAX_DISTANCE),
  NewPing(7, 6, MAX_DISTANCE),
  NewPing(5, 4, MAX_DISTANCE),
  NewPing(3, 2, MAX_DISTANCE)
};

int flldr = A3;
int frldr = A2;
int blldr = A1;
int brldr = A0;
int flldrval, frldrval, blldrval, brldrval;

int Dir1=8;
int PWM1=9;

int Dir2=11;
int PWM2=10;

int detectRange = 50;
int spdPush = 250; //*
int spdRotate = 110;

void setup() {
  pinMode(Dir1,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(Dir2,OUTPUT);
  pinMode(PWM2,OUTPUT);
  Serial.begin(115200);
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1)
        oneSensorCycle(); // Do something with results.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
  // The rest of your code would go here.
}

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
  if (((cm[0]!=0&&cm[0]<detectRange)&&(cm[1]!=0&&cm[1]<detectRange)))
  {
    Serial.println("Case 1 , forward");
    Forward(spdPush,spdPush);
    delay(500);
  }
  
  else if (((cm[2]!=0)&&(cm[2]<detectRange))&&((cm[3]!=0)&&(cm[3]<detectRange)))
  {
    Serial.println("Case 2, backward");
    Backward(spdPush,spdPush);
    delay(350);
  }

  else if ((cm[1]!=0)&&(cm[1]<detectRange))
  {
    Serial.println("Case 3, FL or BR detect");
    RotateLeft(spdRotate,spdRotate);
    delay(100);
  }

  else if ((cm[4]!=0)&&(cm[4]<detectRange))
  {
    Serial.println("Case 3, FL or BR detect");
    RotateLeft(spdRotate,spdRotate);
    delay(100);
  }

  else if ((cm[2]!=0)&&(cm[2]<detectRange))
  {
    Serial.println("Case 4, FR or BL detect");
    RotateRight(spdRotate,spdRotate);
    delay(100);
  }

  else if ((cm[3]!=0)&&(cm[3]<detectRange))
  {
    Serial.println("Case 4, FR or BL detect");
    RotateLeft(spdRotate,spdRotate);
    delay(100);
  }
  
  
  else if ((cm[0]==0)&&(cm[1]==0)&&(cm[2]==0)&&(cm[2]==0))
  {
    Serial.println("Case 5, rotate");
    RotateLeft(spdRotate,spdRotate);
  }
  else
  {
    Serial.println("Case 6, rotate");
    RotateLeft(spdRotate,spdRotate);
  }
  checkLDR();
}

void checkLDR()
{
  flldrval = digitalRead(flldr);
  frldrval = digitalRead(frldr);
  blldrval = digitalRead(blldr);
  brldrval = digitalRead(brldr);
  
  if (flldrval==0||frldrval==0)
  {
    Backward(spdPush,spdPush);
    delay(500);
    //dirToggle = 1;
  }
  else if (blldrval==0||brldrval==0)
  {
    Forward(spdPush,spdPush);
    delay(500);
    //dirToggle = 0;
  }
  else
  {
    RotateLeft(spdRotate,spdRotate);
  }
}

/************************Motor Fucntions************************/
void Forward(int SpdL, int SpdR)
{
  Move(0,SpdL,0,SpdR);
}
void Backward(int SpdL, int SpdR)
{
  Move(1,SpdL,1,SpdR);
}
void RotateLeft(int SpdL, int SpdR)
{
  Move(1,SpdL,0,SpdR);
}
void RotateRight(int SpdL, int SpdR)
{
  Move(0,SpdL,1,SpdR);
}
void LeftMF (int SpdL){  //Left Motor move only (Forward Direction)
  Move(0,SpdL,0,0);
}
void LeftMB (int SpdL){  //Left Motor move only (Backward Direction)
  Move(1,SpdL,0,0);
}
void RightMF (int SpdR){  //Right Motor move only (Forward Direction)
  Move(0,0,0,SpdR);
}
void RightMB (int SpdR){  //Right Motor move only (Backward Direction)
  Move(0,0,1,SpdR);
}

void Move(int MotorDir1,int Spd1,int MotorDir2,int Spd2)
{
  digitalWrite(Dir1,MotorDir1);
  analogWrite(PWM1,Spd1);
  digitalWrite(Dir2,MotorDir2);
  analogWrite(PWM2,Spd2);
}

void Stop()
{
  Move(0,0,0,0);
}
