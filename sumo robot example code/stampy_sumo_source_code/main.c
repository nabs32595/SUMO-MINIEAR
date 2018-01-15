//www.societyofrobots.com December, 2006

#include "cereb104.h"
#include "Utilities.h"


signed long int scan_angle=0; //angle of IR servo
unsigned int target_distance=0; //distance away of target
unsigned int distance_thresh=30; //acceptable target detection


//sense
void scan()
	{
	//swap scan directions
	
	/*psuedocode
	while object is detected
		scan left while object detected
	while object not detected
		scan right until object detected*/
	
	target_distance = analog(A3);//check sensor
	
	if (target_distance > distance_thresh)//object detected
		{
		if (scan_angle>-20) //overflow protection
			scan_angle-=1;//scan left
		}
	else //object not detected
		{
		if (scan_angle<130) //overflow protection
			scan_angle+=1; //scan right
		else //if scanned all the way, this forces it to start over
			scan_angle=-20;
		}
		
	//servo scan code
	output_bit(PIN_D2, 1);//139 center
	long_delay_us(130+scan_angle);
	output_bit(PIN_D2, 0);
		
	//printf("angle: %ld distance: %u\r\n", scan_angle, target_distance);//debug code
	}
	

void main() {

//initializing all Cerebellum routines
cereb_init(0);
pwm_init();

//allow short capacitor charge up time
delay_us(5000);

ScanLeft(); //reset IR scanner to straight

//system ready indicator, and start button
set_led(YELLOW, 1);
while(analog(A3) < 100) {printf("%u\r\n", analog(A3));}; //hand swipe to activate robot
set_led(YELLOW, 0);

servoReverse();

while(1)
	{
	delay_us(2500);//so it doesnt change states too fast //2500 works
	
	scan();//locate target
	
	
	//movement actions
	if (scan_angle > 85)//if target is too far on right
		{
		servoRight();//turn towards target
		set_led(YELLOW, 0);
		set_led(GREEN, 1);
		scan_angle-=1;//scanner turns left while robot turns right
		}
	else if (scan_angle < 50)//if target is too far on left
		{
		servoLeft();//turn towards target
		set_led(YELLOW, 1);
		set_led(GREEN, 0);
		scan_angle+=1;//scanner turns right while robot turns left
		}
	else //centered on target
		{
		servoForward();//drive straight
		set_led(YELLOW, 1);
		set_led(GREEN, 1);
		}
	}
	
while(1);
}

//thoughts, try reducing the 5000 delay, maybe doubling negative scan_angle, and reducing turning speed