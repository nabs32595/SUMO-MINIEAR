// EDGE SENSOR
#define back  3
#define right 7
#define left 8

//SIDE SENSOR
#define left_side 2

// FRONT SENSOR
#define left_sensor  A1
#define right_sensor  A3

// MOTOR
#define right_RPWM_Output  5
#define right_LPWM_Output  6
#define left_RPWM_Output  9
#define left_LPWM_Output  10


// =================================
// no obstacle
int left_detection = HIGH;
int right_detection = HIGH;
int back_detection = HIGH;

int sspeed = 50;

void setup()
{
  Serial.begin(9600);
  // side sensor
  pinMode(left_side, INPUT);

  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  // edge sensor
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(back, INPUT);

  //motor
  pinMode(right_RPWM_Output, OUTPUT);
  pinMode(right_LPWM_Output, OUTPUT);
  pinMode(left_RPWM_Output, OUTPUT);
  pinMode(left_LPWM_Output, OUTPUT);

  // front sensor
  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
}

void loop()
{
  int left_detection = digitalRead(left);
  int right_detection = digitalRead(right);
  int back_detection = digitalRead(back);

  int left_side_detection = digitalRead(left_side);

  int distance_left = average(left_sensor);
  int distance_right = average(right_sensor);
  //      LOW = white        HIGH = black


//     Serial.print("  left: ");
//    Serial.print(left_detection);
//     Serial.print("  right: ");
//     Serial.print(right_detection);
//     Serial.print("  back: ");
//     Serial.println(back_detection);
 
//     Serial.print("  side_left: ");
//     Serial.print(left_side_detection);
 
//     Serial.print("  left: ");
//     Serial.print(distance_left);
//     Serial.print("  right: ");
//     Serial.println(distance_right);


  
      sspeed = 80;
      turn_left();

      if( (distance_left > 270 || distance_right > 270) ){
      // green 
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH); 
      sspeed = 255;
      forward();       
      }
//======================================================================================      
      if(left_detection == LOW){
        Serial.print("   line detected on left");
        sspeed = 150;
        backward();
        delay(500
        );

        if(back_detection == HIGH){
             if(distance_left > 270 || distance_right > 2700){
              digitalWrite(12, LOW);
              digitalWrite(11, HIGH); 
              sspeed = 255;
              forward();                 
              }     
        }else{
              sspeed = 255;
              forward();
              if(distance_left > 270 || distance_right > 270){
              digitalWrite(12, LOW);
              digitalWrite(11, HIGH); 
              sspeed = 255;
              forward();
              }  
        }
        if(distance_left > 270 || distance_right > 270){
          digitalWrite(12, LOW);
          digitalWrite(11, HIGH); 
          sspeed = 255;
          forward();                 
        }                 
      }

//======================================================================================
       else if(right_detection == LOW){
        Serial.print("   line detected on right");
        sspeed = 150;
        backward();
        delay(500);

        
         if(back_detection == HIGH){ 
           if(distance_left > 270 || distance_right > 270){
          digitalWrite(12, LOW);
          digitalWrite(11, HIGH); 
          sspeed = 255;
          forward();                
          }           
        }else{
          sspeed = 255;
          forward();
          if(distance_left > 270 || distance_right > 270){
          digitalWrite(12, LOW);
          digitalWrite(11, HIGH); 
          sspeed = 255;
          forward();                
          }           
        }
                 
      }
//==============================================================================
       else if(back_detection == LOW){
        Serial.print("   line detected on right");
        sspeed = 255;
        forward();

        if(distance_left > 270 || distance_right > 270){
          digitalWrite(12, LOW);
          digitalWrite(11, HIGH); 
          sspeed = 255;
          forward();       
                 
        }                 
      }

      else if(right_detection == LOW && left_detection == LOW){
        Serial.print("   line detected on right and right");
        sspeed = 255;
        backward();
        delay(500);

        if(distance_left > 270 || distance_right > 270){
          digitalWrite(12, LOW);
          digitalWrite(11, HIGH); 
          sspeed = 255;
          forward();       
                 
        }                 
      }

              
}

int average(int pin){
  int total;
  for(int x=0; x < 3; x++){
    total = total + analogRead(pin);
  }
  
return total/3;  
}


