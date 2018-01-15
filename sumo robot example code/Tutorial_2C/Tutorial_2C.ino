#define Right_Dir1   8 //in3
#define Right_Dir2   7 //in4
#define Right_Speed  6 //enB

#define Left_Dir1   12 //in1
#define Left_Dir2   13 //in2
#define Left_Speed  11 //enA

// Nominal speed
int nom_Rspeed = 255;//100-20;
int nom_Lspeed = 255;

void setup() {
  // put your setup code here, to run once:

  pinMode(Right_Dir1, OUTPUT);  //Initialize pin 8 as an DIGITAL OUTPUT pin
  pinMode(Right_Dir2, OUTPUT);  //Initialize pin 7 as an DIGITAL OUTPUT pin
  pinMode(Left_Dir1, OUTPUT); //Initialize pin 12 as an DIGITAL OUTPUT pin
  pinMode(Left_Dir2, OUTPUT); //Initialize pin 13 as an DIGITAL OUTPUT pin
 
  Serial.begin(9600); // Setup serial communication

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Forward();
  Go(nom_Lspeed,nom_Rspeed);

}
