//left -> counterclockwise=forward= 1100
//right -> clockwise = forward = 1900


inline void servoLeft()//slow left turn
	{
	output_bit(PIN_D0, 1);//139 center
	delay_us(1400);
	output_bit(PIN_D0, 0);

	output_bit(PIN_D1, 1);//139 center
	delay_us(1800);
	output_bit(PIN_D1, 0);
	}

inline void servoRight()//fast right turn
	{
	output_bit(PIN_D0, 1);//139 center
	delay_us(1100);
	output_bit(PIN_D0, 0);

	output_bit(PIN_D1, 1);//139 center
	delay_us(1300);
	output_bit(PIN_D1, 0);
	}

inline void servoForward()//go forward
	{
	output_bit(PIN_D0, 1);//139 center
	delay_us(1000);
	output_bit(PIN_D0, 0);

	output_bit(PIN_D1, 1);//139 center
	delay_us(1900);
	output_bit(PIN_D1, 0);
	}
	
inline void servoReverse()//go forward
	{
	int i=250;
	while (i>0)
		{
		output_bit(PIN_D0, 1);//139 center
		delay_us(1900);
		output_bit(PIN_D0, 0);
	
		output_bit(PIN_D1, 1);//139 center
		delay_us(1000);
		output_bit(PIN_D1, 0);
		
		i--;
		}
	}

inline void ScanRight()
	{
	int i=3;
	
	while(i>0)
		{
		output_bit(PIN_D2, 1);//139 center
		delay_us(1500);
		output_bit(PIN_D2, 0);
		delay_us(2000);
		i--;
		}
	}

inline void ScanLeft()
	{
	int i=3;
	
	while(i>0)
		{
		output_bit(PIN_D2, 1);//139 center
		delay_us(900);
		output_bit(PIN_D2, 0);
		delay_us(2000);
		i--;
		}
	}

void long_delay_us(long int timing)
	{
	int i=10;
	while (i--)
		{
		delay_us(timing);
		}
	}