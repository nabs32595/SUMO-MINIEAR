void setup() {
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  int pinvalue = analogRead(8);
  Serial.println(pinvalue);
  delay(500);
}
