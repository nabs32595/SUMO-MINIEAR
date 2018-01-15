/*
  3/20/04 PWM routine for Cereb 1.00 - 1.04 +
  by bkirby

  ******************
  Primary functions:
  ******************
  pwm_init()
  set_pwm(int which, signed long int open_velocity)
  set_pwms(signed long int open_velocity1, signed long int open_velocity2)


  *********************
  Function Descriptions
  *********************

  pwm_init():
    Call this once before attempting to use either set_pwm or set_pwms.  
    Usually called at the beginning of your main() loop.
  
  set_pwm(), set_pwms():

    int which: 
             'which' may either be 0 or 1.  You may also use 
             MOTOR_1 and MOTOR_2, as I have defined them.

    signed long int open_velocity: 
             a value in the range -1023 <-> 1023.
	     -1023 is full reverse, 0 is off, 1023 is full forward.
	     Anything great in absolute value than 1023 will be truncated.
      
  set_pwm() allows you to set one motor direction/duty cycle at a time.
  set_pwms() sets both motors dir/duty cycle simultaneously.

*/

#define H_DIR1B PIN_C0
#define H_DIR1A PIN_A4

#define H_DIR2B PIN_C5
#define H_DIR2A PIN_B1

#define H_MAX_SPEED 1023

#define MOTOR_1 0
#define MOTOR_2 1

inline void set_hbridge_backward(int which)
{
  if(which == MOTOR_1)
    {
      output_low(H_DIR1A);
      output_high(H_DIR1B);
    }
  else
    {
      output_low(H_DIR2A);
      output_high(H_DIR2B);
    }
}

inline void set_hbridge_forward(int which)
{
  if(which == MOTOR_1)
    {
      output_high(H_DIR1A);
      output_low(H_DIR1B);
    }
  else
    {
      output_high(H_DIR2A);
      output_low(H_DIR2B);
    }
}

inline void set_hbridge_speed(int which, long int spd)
{
  if(spd > H_MAX_SPEED)
    spd = H_MAX_SPEED;

  if(which == MOTOR_1)
    {
      set_pwm1_duty(spd);
    }
  else
    {
      set_pwm2_duty(spd);
    }
}

void set_hbridge_speeds(long int spd1, long int spd2)
{
  set_hbridge_speed(MOTOR_1, spd1);
  set_hbridge_speed(MOTOR_2, spd2);
}

void set_hbridge_duty(int which, signed long int v)
{
  if(v > 0)
    {
      set_hbridge_forward(which);
    }
  else
    {
      v *= -1;

      set_hbridge_backward(which);
    }

  set_hbridge_speed(which, v);
}

inline void set_hbridge_duties(signed long int v1, signed long int v2)
{
  set_hbridge_duty(MOTOR_1, v1);
  set_hbridge_duty(MOTOR_2, v2);
}

void pwm_init()
{
  setup_ccp1(CCP_PWM);
  setup_ccp2(CCP_PWM);
  setup_timer_2(T2_DIV_BY_1, 255, 1);

  set_hbridge_speeds(0,0);
}

#define set_pwm(x,y) set_hbridge_duty(x,y)
#define set_pwms(x,y) set_hbridge_duties(x,y)
