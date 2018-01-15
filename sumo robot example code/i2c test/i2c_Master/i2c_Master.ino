#include <Wire.h>

  // EDGE SENSOR
  int left = 8;
  int right = 6;
  int back = 7;
  
  // FRONT SENSOR
  int left_sensor = A1;
  int center_sensor = A2;
  int right_sensor = A3;
  
  // no obstacle  
  int left_detection = HIGH;
  int right_detection = HIGH;
  int back_detection = HIGH;

void setup(){
  
  Serial.begin(9600);
  Wire.begin(5);
    
  // edge sensor
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(back, INPUT);

  // front sensor
  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(center_sensor, INPUT);
  
}

void loop() {
  int data [6];
  
  // edge sensor 
  int left_detection = digitalRead(left);
  int right_detection = digitalRead(right);
  int back_detection = digitalRead(back);

  //  the distance of front sensor (cm)
  int distance_left = average_value(100, left_sensor);                    
  int distance_right = average_value(100, right_sensor);
  int distance_center = average_value(100, center_sensor);  
  // LOW = white HIGH = black

  data [0] = left_detection;
  data [1] = right_detection;
  data [2] = back_detection;
  
  data [3] = distance_left;
  data [4] = distance_right;
  data [5] = distance_center;

Serial.print("left:   ");
Serial.print(data [0]);
Serial.print("   right:  ");
Serial.print(data [1]);
Serial.print("   back:  ");
Serial.print(data [2]);

Serial.print("      left (cm): ");
Serial.print(data [3]);
Serial.print("  right(cm): ");
Serial.print(data [4]);
Serial.print("  center(cm): ");
Serial.println(data [5]);
  
  Wire.beginTransmission(5);
  Wire.write((byte *) data, sizeof data);
  Wire.endTransmission(5);
    
}

int average_value(int average_count, int sensor_pin ) {
  int sum = 0;
  for (int i=0; i<average_count; i++) {
    int sensor_value = analogRead(sensor_pin);             
    int distance_cm = pow(3027.4/sensor_value, 1.2134);   
    sum = sum + distance_cm;
  }
  return(sum/average_count);  
}


