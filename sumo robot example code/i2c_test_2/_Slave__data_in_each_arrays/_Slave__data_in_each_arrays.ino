#include <Wire.h>
int table[]={0,0,0};
int Work=0;

void setup() {
Wire.begin(8);                // join i2c bus with address #8
Wire.onRequest(requestEvent); // register event
Wire.onReceive(receiveEvent); // register event
}

void loop() {
int x=120;  
int y=1200;// gets converted to a strange # because is larger than 255
int z=3;
  table[0]=x;
  table[1]=y;
  table[2]=z;
}


void requestEvent()
{
  uint8_t Buffer[3];
  Buffer[0]=table[0];
  Buffer[1]=table[1];
  Buffer[2]=table[2];
  Wire.write(Buffer,3);
}

void receiveEvent(int howMany)
{Work = Wire.read();}
