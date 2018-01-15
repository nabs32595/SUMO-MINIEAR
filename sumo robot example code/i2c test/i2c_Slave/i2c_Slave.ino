#include <Wire.h>

// MOTOR
int right_RPWM_Output = 5; 
int right_LPWM_Output = 6; 
int left_RPWM_Output = 10; 
int left_LPWM_Output = 11;

void setup() 
{
  Serial.begin(9600);
  Wire.begin(5);
  
  //motor
  pinMode(right_RPWM_Output, OUTPUT);
  pinMode(right_LPWM_Output, OUTPUT);  
  pinMode(left_RPWM_Output, OUTPUT);
  pinMode(left_LPWM_Output, OUTPUT);

}

void loop(){
  int data[6];
  
  byte index = 0;
  while (index < 6)
  {
    data[index] = Wire.read();
    index++;
  }

  int left_detection = data [0];
  int right_detection = data [1];
  int back_detection = data [2];
  
  int distance_left = data [3];
  int distance_right = data [4];
  int distance_center = data [5];

Serial.print("left:   ");
Serial.print(left_detection);
Serial.print("   right:  ");
Serial.print(right_detection);
Serial.print("   back:  ");
Serial.print(back_detection);

Serial.print("      left (cm): ");
Serial.print(distance_left);
Serial.print("  right(cm): ");
Serial.print(distance_right);
Serial.print("  center(cm): ");
Serial.println(distance_center);
    
}

