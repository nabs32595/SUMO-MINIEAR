#include <16F877.h>
#fuses HS, NOWDT
#use delay (clock = 20000000)
#use rs232(baud=115200, parity=N, bits=8, xmit=PIN_C6, rcv=PIN_C7)

#include <cereb104-pinout.h>
#include <cereb10-pwm.h>
#include <cereb10-adc.h>

/*
  OPTION FLAGS for cereb_init()

DISABLE_ANALOG - does not call analog_init()
DISABLE_PWM    - does not call pwm_init()
*/
#define DISABLE_ANALOG 0x01
#define DISABLE_PWM    0x02

// for LEDs
#define YELLOW 1
#define GREEN 0

// for buttons
#define BTN_A 0
#define BTN_B 1

// ADC ports

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A5 4
#define E0 5
#define E1 6
#define E2 7

// turn a specified(0 or 1) LED on.
void set_led(int which, int value)
{
  if(which == GREEN)
    {
      output_bit(GREEN_LED_PIN, value);
    }
  else
    {
      output_bit(YELLOW_LED_PIN, value);
    }

}

#define LEDon(x) set_led(x, 1)
#define LEDoff(x) set_led(x, 0)

int button(int which)
{
   if(which == BTN_A)
     {
	return input(BTN_A_PIN);
     }
   else
     {
	return input(BTN_B_PIN);
     }
}

inline void waitforbutton(int which)
{
  while(!button(which))
    {
      delay_ms(10);
    }
}

/*
  To add:

  flags so you can cereb_init(BLAH | BLAH | BLAH); to turn off various things,
  maybe enable special options(like analog settings).

*/
inline void cereb_init(int flags)
{
  if(!(flags & DISABLE_ANALOG))
    {
      analog_init();
    }

  if(!(flags & DISABLE_PWM))
    {
      pwm_init();
    }

  enable_interrupts(GLOBAL);
  delay_ms(1);
}
