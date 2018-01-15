int left_sensor =  A1;
int right_sensor =  A2;
int back_sensor  = A3;

void setup() {
Serial.begin(9600);
pinMode(left_sensor, INPUT);
pinMode(right_sensor, INPUT);
pinMode(back_sensor, INPUT);
}

void loop() {
int Left_sensor_reding = analogRead(left_sensor);
int right_sensor_reding = analogRead(right_sensor);
int back_sensor_reding = analogRead(back_sensor);

delay(300);

Serial.print("  left: ");
Serial.print(Left_sensor_reding);
Serial.print("  right: ");
Serial.print(right_sensor_reding);
Serial.print("  back: ");
Serial.println(back_sensor_reding);

}
