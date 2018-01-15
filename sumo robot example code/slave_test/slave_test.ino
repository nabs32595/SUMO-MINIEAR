#include <Wire.h> 
int left_reading;
//int right_reading;
//int back_reading;
//int data [] = {0,0,0};
//int i;

void setup()
{
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  Wire.begin(5);  
}
 
void loop()
{ 
    digitalWrite(3, HIGH);  
    left_reading = Wire.read() ;
    //left_reading |= Wire.read();
    Serial.println(left_reading);

    
  /*
  for(int i=0; i < 3; i++){
    int c = Wire.read();
    Serial.print(c);
    data[i] = c;
    Serial.print('\t');   
  }

  if (i == 3)  // All bytes received?
  {
    digitalWrite(3, HIGH);
    left_reading =  data[0];
    right_reading = data[1];
    back_reading =  data[2];
    
    
    Serial.print("  Left: "  );
    Serial.print(left_reading);
    Serial.print("  right: "  );
    Serial.print(right_reading);
    Serial.print("  back: "   );
    Serial.println(right_reading);
  }
  else
  {
    digitalWrite(5, HIGH);
    Serial.println("!ERR: No Reading");
  }
  
 */ 
  
}
