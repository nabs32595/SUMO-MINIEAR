#define left 1;
#define right 2;
#define back 3;


// no obstacle  
int left_detection = HIGH;
int right_detection = HIGH; 
int back_detection = HIGH;     

void setup() {
  Serial.begin(9600);   
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(back, INPUT); 
}
void loop() {  
  left_detection = digitalRead(left);
  right_detection = digitalRead(right);
  back_detection = digitalRead(back);
  

  
  delay(500);    // in ms
}
