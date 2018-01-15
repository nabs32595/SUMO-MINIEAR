#define left A1
#define right A3

void setup () {
  Serial.begin (9600);
  pinMode (left, INPUT);
  //pinMode (right, INPUT);
}

void loop () {
  uint16_t value = analogRead (left);
  uint16_t range = get_gp2d12 (value);
  Serial.println (value);
  Serial.print (range);
  Serial.println (" mm");
  Serial.println ();
  delay (500);
}

uint16_t get_gp2d12 (uint16_t value) {
  if (value < 10) value = 10;
  return ((67870.0 / (value - 3.0)) - 40.0);
}

