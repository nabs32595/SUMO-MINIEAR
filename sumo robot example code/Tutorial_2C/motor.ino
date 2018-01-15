void Forward()
{
  Left_Forward(); // CCW
  Right_Forward(); // CW
}

//======================================

void Left_Forward() // CCW
{
  digitalWrite(Left_Dir1, HIGH);
  digitalWrite(Left_Dir2, LOW);
}

void Right_Forward() //CW
{
  digitalWrite(Right_Dir1, LOW);
  digitalWrite(Right_Dir2, HIGH);
}

//=======================================

void Go(int a, int b) // a for motor right speed & b for motor left speed
{
  analogWrite(Left_Speed, a);
  analogWrite(Right_Speed, b);
}
