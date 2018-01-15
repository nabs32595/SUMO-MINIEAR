/*
  This sets the setup time on the ADC.  For most low impedance
  loads, 10 us is fine.  Only alter if you experience problems.
*/
#define CEREB_10_ANALOG_READ_DELAY 10

inline void analog_init()
{
  setup_adc_ports(ALL_ANALOG);
  setup_adc(ADC_CLOCK_INTERNAL);
}

/*
  Refer to the 16f877.h file and PIC manual for proper definitions
*/
void analog_custom_init(byte ports, byte clock)
{
  //setup_adc_ports(ports);
  //setup_adc(clock);
  #define analog_custom_init(__PORTS,__CLOCK) setup_adc_ports(__PORTS) setup_adc(__CLOCK);
}

/*
  Returns 0-255, 0 -> 0V, 255 -> 5V (with standard 5V reference)

*/
unsigned int analog(int channel)
{
  set_adc_channel(channel);
  delay_us(CEREB_10_ANALOG_READ_DELAY);
  return read_adc();
}
