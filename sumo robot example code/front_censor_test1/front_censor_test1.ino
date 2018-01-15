int left = A0;
int right = A1;

void setup() {
  Serial.begin(9600);
  pinMode(left, INPUT);
  pinMode (right, INPUT);
}

void loop() {
 int left_reding = analogRead(left);
 int right_reding = analogRead(right);  

  delay(500);
  Serial.print("    Left: ");
  Serial.print(left_reding); 
  Serial.print("   right:  ");
  Serial.println(right_reding);
  
}
