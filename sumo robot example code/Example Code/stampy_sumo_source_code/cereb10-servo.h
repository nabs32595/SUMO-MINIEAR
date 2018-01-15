#byte PORTD = 0x08
#byte TRISD = 0x88

#define DEFAULT_CEREB_SERVO_OFFSET 82
#define DEFAULT_CEREB_SERVO_MULTIPLIER 6
#define DEFAULT_CEREB_SERVO_DIVISOR 5

unsigned int cereb_servo_offset = DEFAULT_CEREB_SERVO_OFFSET;
long int cereb_servo_multiplier = DEFAULT_CEREB_SERVO_MULTIPLIER;
long int cereb_servo_divisor = DEFAULT_CEREB_SERVO_DIVISOR;

char cereb_servo_state = 0;
char cereb_servo_curr = 0;
long int cereb_servo_time_left = 75;
char cereb_servo_switch = 1;
char cereb_servo_pos[8] = {0};

byte cereb_servo_mask = 0;

/*
  TIMER0 servo output routine

  Do not modify.  Thanks.
*/
#INT_RTCC
void cereb_servo_isr(void) {

  if(cereb_servo_mask)
    {
      if (cereb_servo_state == 0) 
	{
	  // next intr in 0.6 ms
	  if(cereb_servo_time_left > 255)
	    {
	      set_timer0(0);
	      cereb_servo_time_left -= 255;
	    }
	  else
	    {
	      set_timer0(255 - ((int)cereb_servo_time_left));
	      cereb_servo_time_left = 0;
	    }
	  // If servo is enabled
	  if (cereb_servo_mask & cereb_servo_switch)
	    {
	      // Output high on that pin
	      PORTD = PORTD | cereb_servo_switch;
	    }
	  
	  cereb_servo_switch = cereb_servo_switch << 1;
	  if (cereb_servo_switch == 0) 
	    {
	      cereb_servo_switch = 1;
	    }
	  
	  cereb_servo_state++;
	}
      else if (cereb_servo_state == 1) 
	{
	  set_timer0(255 - ((int)cereb_servo_time_left));
	  cereb_servo_state++;
	}
      else if (cereb_servo_state == 2) 
	{
	  PORTD = PORTD & ~cereb_servo_mask;

	  // Alter to adjust pwm frequency (lower number = lower frequency)
	  set_timer0(0); 
	  
	  /* Cycle from 0 - 7, resetting at 8. */
	  cereb_servo_curr++;
	  cereb_servo_curr = cereb_servo_curr & 0x07;
	  
	  cereb_servo_time_left = cereb_servo_offset + (((long int)cereb_servo_pos[cereb_servo_curr])*cereb_servo_multiplier)/cereb_servo_divisor;
	  cereb_servo_state = 0;
	}
      else
	{
	  cereb_servo_state = 0;
	}
    }

}

/*
  Use this to set a single servo on/off.

  Use set_servo_mask to quickly set more than one at a time.
*/
void enable_servo(int which)
{
  cereb_servo_mask |= (0b00000001 << which);
  TRISD = (TRISD & ~cereb_servo_mask);
}

/*
  Use this to disable a servo.

  Use set_servo_mask to quickly disable more than one at a time.
*/
void disable_servo(int which)
{
  cereb_servo_mask &= (0xFF ^ (0b00000001 << which));
  TRISD = (TRISD & ~cereb_servo_mask);
}

inline void servo_init()
{
  setup_timer_0(RTCC_DIV_32 | RTCC_INTERNAL);
  enable_interrupts(INT_RTCC);
}

void reset_servo_calibration()
{
  cereb_servo_offset = DEFAULT_CEREB_SERVO_OFFSET;
  cereb_servo_multiplier = DEFAULT_CEREB_SERVO_MULTIPLIER;
  cereb_servo_divisor = DEFAULT_CEREB_SERVO_DIVISOR;
}

/* Servos are tuned to receive pulses.  By setting the value to 0-255,
   you achieve a range of pulse widths.  Different brands of servos sometimes
   behave differently, so it helps to be able to tune the pulses.

  The equation is as follows:

  pulse length = 6.7 us * (offset + mult*[value]/div)
  
  Using values of 82, 6, 5, you get a range of .55 ms to 2.5ms, which
  will drive a HS-311 servo in its entirety, plus a bit(avoid 253+ if you can).

  Using values of 150, 3, 5, you get a range of 1 ms to 2 ms, which is what servos
  usually get from a receiver.

  Use as necessary.  Use reset_servo_calibration() if necessary to restore to the defaults.
*/
void calibrate_servos(unsigned int offset, long int mult, long int div)
{
  cereb_servo_offset = offset;
  cereb_servo_multiplier = mult;
  cereb_servo_divisor = div;
}

/*
  Use this to quickly setup which pins on the D port are for servos.

  Each bit in the 8-bit number corresponds to whether each of the 8
  pins is enabled or disabled.

  0b00000000 or 0x00 -> all off
  0b11111111 or 0xFF -> all on
  0b11110000 or 0xF0 -> D7 - D4 on, D3 - D0 normal digital I/O.
  0b10100111 or 0xA7 -> D7, D5, D2, D1, D0 are servos, rest are I/O.

  You may also use enable_servo() and disable_servo() to set them
  individually.
*/
void set_servo_mask(byte mask)
{
  cereb_servo_mask = mask;
  TRISD = TRISD & ~cereb_servo_mask;
}

/*
  Give the servo a value from 0 - 255.
  Use enable_servo first, or the servo will not move.
  Use disable_servo to stop sending signals to it.
*/
#define set_servo(x,y) (cereb_servo_pos[x] = y)
