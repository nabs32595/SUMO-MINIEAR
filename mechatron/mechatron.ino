// ULTRASONIC    
#define  trigPin_Left A0              
#define  echoPin_Left  A1              
#define  trigPin_Right  A2             
#define  echoPin_Right  A3    

unsigned long pulseTime = 0; 
unsigned long distance = 0;
unsigned long distance_Left = 0;   
unsigned long distance_Right = 0;  

//  LINE
#define left 3
#define right 4
#define back 2

int left_detection = HIGH;
int right_detection = HIGH; 
int back_detection = HIGH;

//   MOTOR
#define  right_RPWM_Output  10 
#define  right_LPWM_Output  11 
#define  left_RPWM_Output 5
#define  left_LPWM_Output  6

 int speedy = 255;
 
void setup() {

  Serial.begin(57600);
  
  // motor
  pinMode(right_RPWM_Output, OUTPUT);
  pinMode(right_LPWM_Output, OUTPUT);  
  pinMode(left_RPWM_Output, OUTPUT);
  pinMode(left_LPWM_Output, OUTPUT);

  // ultrasonic
  pinMode(trigPin_Left, OUTPUT);
  pinMode(echoPin_Left, INPUT);
  pinMode(trigPin_Right, OUTPUT);
  pinMode(echoPin_Right, INPUT);
  
  // line sensor
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(back, INPUT);
 }

void loop() 
{
  // ultrasonic
  distance_Left = calculateDistance(trigPin_Left,echoPin_Left);
  distance_Right = calculateDistance(trigPin_Right,echoPin_Right);

  Serial.print(" left ");
  Serial.print(distance_Left);                                  
  Serial.print("cm  ");
  Serial.print(" right ");
  Serial.print(distance_Right);
  Serial.print("cm  ");
  


//line sensor

  left_detection = digitalRead(left);
  right_detection = digitalRead(right);
  back_detection = digitalRead(back);
  
  Serial.print("  Left:  ");
  Serial.print(left_detection);
  Serial.print("  Right:  ");
  Serial.print(right_detection);
  Serial.print(" Back: ");
  Serial.println(back_detection);

      speedy = 100;
      turn_right();
      
    /*  if(distance_Left < 60 || distance_Right < 60){
        Serial.println("enemy");
        speedy = 255;
        forward();
      }
      
      if(left_detection == LOW){
        Serial.print("   line detected on left");
        speedy = 150;
        backward();
        delay(500);
        speedy = 100;
        turn_left();
        delay(500);

        if(distance_Left < 60 || distance_Right < 60){
        Serial.println("enemy");
        speedy = 255;
        forward();
        }       
                 
        }                 
      

       else if(right_detection == LOW){
        Serial.print("   line detected on right");
        speedy = 150;
        backward();
        delay(500);
        speedy = 100;
        turn_right();
        delay(500);

        if(distance_Left < 60 || distance_Right < 60){
        Serial.println("enemy");
        speedy = 255;
        forward();
        }        */   
      }

        
}
int calculateDistance (int trigPin,int echoPin)
{
  
   digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pulseTime = pulseIn(echoPin, HIGH); 
  distance = pulseTime/58;                               
  return distance;
}
  
  
  


