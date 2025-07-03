#include <avr/io.h>

// #include <util/delay.h> this is a blocking delay mechanism which does nothing in those cpu clock cycle for which it is defined, meaning the program gets stuck in between intructions for that time i.e. one second. To overcome this issue, an approach is to use non blocking timer/counter, which can be used by the TCINT0 register that's an 8-bit timer/counter register


#define GREEN_LED PD5

volatile uint16_t timer_ms_count = 0;

void setup() {
  DDRD |= (1 << GREEN_LED); //Set GREEN_LED as output
  
  //1. Set Timer0 for normal mode 
  TCCR0A = 0;
  TCCR0B = 0;
  
  TCCR0B |= (1 << CS00) | (1 << CS01);


}

int main(int argc, char *argv[])
{
  setup();

  uint32_t last_blink_time = 0;
  uint32_t blink_interval = 1000;

  while (1) {
    if (TIFR0 & (1 << TOV0)) {
      timer_ms_count++;
      TIFR0 |= (1 << TOV0);

    }
    
    if (timer_ms_count - last_blink_time >= blink_interval) {
      PORTD ^= (1 << GREEN_LED);
      last_blink_time = timer_ms_count;
    }

  }
  return 0;
}
