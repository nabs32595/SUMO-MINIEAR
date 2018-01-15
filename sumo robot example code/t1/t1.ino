
int right_RPWM_Output = 5; 
int right_LPWM_Output = 6; 
int left_RPWM_Output = 10; 
int left_LPWM_Output = 11;


void setup()
{
  Serial.begin(57600);
  //motor
  pinMode(right_RPWM_Output, OUTPUT);
  pinMode(right_LPWM_Output, OUTPUT);  
  pinMode(left_RPWM_Output, OUTPUT);
  pinMode(left_LPWM_Output, OUTPUT);

}

void loop()
{
delay(1500);
leftrunaway();
}

