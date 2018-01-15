#include <Servo.h>

Servo leftWheel;
Servo rightWheel;
int leftWheelPin = 3; // These are digital PWM pins
int rightWheelPin = 11;

int mspeed = 200; // Variable that will be added to lspeed & rspeed to set a precise speed
int lspeed = 1530; // Signal sent that stops left motor
int rspeed = 1535; // Signal sent that stops right motor
// Signal of ~1300 turns motor clockwise at full speed
// Signal of ~ 1700 turns motor coutner-clockwise at full speed

int leftEyePin = A2;
int rightEyePin = A0;
int leftEyeVal;
int rightEyeVal;
int dist = 250; // Distance within which the robot will react, roughly 10cm

int leftGS = A5; // GS = Ground Sensor
int rightGS = A4;
int leftGSVal;
int rightGSVal;
int GSthresh; // Threshold used to detect if robot has moved from black surface to white
// This code assumes that a black surface provides a high signal.

void setup()
{
  leftWheel.attach(leftWheelPin); // Initialise the servos
  rightWheel.attach(rightWheelPin);
  
  GSthresh=((analogRead(leftEyePin)+analogRead(rightEyePin))/2)-300; // Calculate the threshold for ground sensors
  // This line takes the values seen in the two ground sensors. It assumes that the robot is starting on the black surface
  // We get the average of the two values and reduce by 300.
  // This value of 300 is ideal for ground sesnors that are 3mm above the ground. Smaller value will be needed if the sensors are higher than 3mm
  // If either eye gives a signal that is 300 under the average value of black, we must be on white.
}

// Main Loop
void loop()
{
  turnLeft(); // We start off initially by turning left to find the opponent
  
  // Check the ground to see if we are at the edge of the ring
  leftGSVal = analogRead(leftGS);
  rightGSVal = analogRead(rightGS);
  if(leftGSVal<GSthresh||rightGSVal<GSthresh) {survive();}
  
  // Look for opponent
  leftEyeVal = analogRead(leftEyePin);
  rightEyeVal = analogRead(rightEyePin);
  if(leftEyeVal>dist&&rightEyeVal>dist) {attack();} // If enemy is seen in both eyes
  if(leftEyeVal>dist) {hunt(true);} // Seen in left eye
  if(rightEyeVal>dist) {hunt(false);} // Seen in right eye
  
  delay(20);
}

void hunt(boolean left) // Called when enemy is seen in just one eye.
// We must tell the function which eye the enemy was seen in
// This will only require a boolean
{
  if(left==true) {turnLeft();}
  else {turnRight();}
  
  delay(20);
  
  // Check the ground for the edge of the ring
  leftGSVal = analogRead(leftGS); // Must make this check as often as possible
  rightGSVal = analogRead(rightGS);
  if(leftGSVal<GSthresh||rightGSVal<GSthresh) {survive();}
  
  leftEyeVal = analogRead(leftEyePin); // This time we are calling the function recursivly,
  rightEyeVal = analogRead(rightEyePin);
  if(leftEyeVal>dist&&rightEyeVal>dist) {attack();} // If enemy is seen in both eyes
  if(leftEyeVal>dist) {hunt(true);} // Seen in left eye
  if(rightEyeVal>dist) {hunt(false);} // Seen in right eye
  
  return;
}

void attack() // Called when enemy is seen in both eyes
{
  while(leftEyeVal>dist&&rightEyeVal>dist) // We only continue driving forward so long as the opponent is seen in both eyes
  {
    driveForward();
    
    delay(20);
    
    leftGSVal = analogRead(leftGS); // Once again, keeping an eye on the edge of the ring
    rightGSVal = analogRead(rightGS);
    if(leftGSVal<GSthresh||rightGSVal<GSthresh) {survive();}
    
    leftEyeVal = analogRead(leftEyePin);
    rightEyeVal = analogRead(rightEyePin);
  }
  if(leftEyeVal>dist) {hunt(true);} // Seen in left eye
  if(rightEyeVal>dist) {hunt(false);} // Seen in right eye
  
  loop; // If we no longer see the opponent in either eye, return to the beginning of the function and begin searching from scratch
}

void survive() // Called when edge of ring is detected
{
  stopWheels();
  
  // If we see the edge of the ring in both eyes
  // Reverse for 0.75 seconds and returns to main loop
  if(leftGSVal<GSthresh&&rightGSVal<GSthresh)
  {
    driveBackward();
    delay(750);
    loop;
  }
  
  // If left side of robot is near the edge
  // Turn left on the spot and reverse
  if(leftGSVal<GSthresh)
  {
    turnLeft();
    delay(175);
    driveBackward();
    delay(750);
    loop; // This turns the robot a bit and then reverses
  }
  
  // If left side of robot is near the edge
  if(rightGSVal<GSthresh)
  {
    turnRight();
    delay(175);
    driveBackward();
    delay(750);
    loop; // Same with this one
  }
}

// Functions called to turn the wheels in a desired way
void turnLeft()
{
  leftWheel.writeMicroseconds(lspeed-mspeed);
  rightWheel.writeMicroseconds(rspeed-mspeed);
  return;
}

void turnRight()
{
  leftWheel.writeMicroseconds(lspeed+mspeed);
  rightWheel.writeMicroseconds(rspeed+mspeed);  
  return; 
}

void stopWheels()
{
  leftWheel.writeMicroseconds(lspeed);
  rightWheel.writeMicroseconds(rspeed); 
  return;
}

void driveForward()
{
  leftWheel.writeMicroseconds(lspeed+mspeed);
  rightWheel.writeMicroseconds(rspeed-mspeed);
  return;
}

void driveBackward()
{
  leftWheel.writeMicroseconds(lspeed-mspeed);
  rightWheel.writeMicroseconds(rspeed+mspeed);
  return;
}
