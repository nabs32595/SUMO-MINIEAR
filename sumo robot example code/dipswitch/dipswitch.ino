int switch_1 = 4;
int switch_2 = 5;
int switch_3 = 6;
int switch_4 = 7;

int state_1;
int state_2;
int state_3;
int state_4;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(switch_1, INPUT);
  pinMode(switch_2, INPUT);
  pinMode(switch_3, INPUT);
  pinMode(switch_4, INPUT);  
}

void loop() {
    
state_1 = digitalRead(switch_1);
state_2 = digitalRead(switch_2);
state_3 = digitalRead(switch_3);
state_4 = digitalRead(switch_4);

Serial.print("  Switch 1:     ");
Serial.print(state_1);
Serial.print("  Switch 2:     ");
Serial.print(state_2);  
Serial.print("  Switch 3:     ");
Serial.print(state_3);  
Serial.print("  Switch 4:     ");
Serial.println(state_4);

delay(500);    
/*
  if(state_1 == HIGH){
  digitalWrite(13, HIGH);      
  }
  else if(state_2 == HIGH){
  digitalWrite(13, HIGH);      
  }
  
  else if(state_3 == HIGH){
  digitalWrite(13, HIGH);      
  }
  
  else if(state_4 == HIGH){
  digitalWrite(13, HIGH);
  }  
  else{
  digitalWrite(13, LOW);     
  }
  
*/  
}
