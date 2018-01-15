#include <Wire.h>

const int SLAVE_ADDRESS = 8; //Slave arduino ID
int table[]={0,0,0}; //the data will be transmited via table as to allow different data to be transfer.
void setup ()
{
Wire.begin ();   
Serial.begin (9600);  // start serial for output
}  // end of setup
void loop()
{
Wire.requestFrom(SLAVE_ADDRESS, 3);// request 3 bytes from slave device #8

for(int i=0;i<3;i++)//organizes the data from the slave in the table
{
int c = Wire.read(); // receive a byte as character
table[i]=c;
}
//displays the data
 Serial.print('\n');
 Serial.print("Data in each arrays:\t");
 
   Serial.print(table[0]);
    Serial.print('\t');
   Serial.print(table[1]);
    Serial.print('\t');
   Serial.print(table[2]);
   Serial.print('\n');

delay (500);   

// transmit just this variable to the slave
int Work=1;
Wire.beginTransmission (8);
Wire.write (Work);
Wire.endTransmission ();
}
