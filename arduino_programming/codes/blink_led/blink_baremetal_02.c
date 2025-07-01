#include "avr/io.h"

#include "util/delay.h"

int main(int argc, char *argv[])
{
  DDRD |= (1 << DDD7); // This set the Data Directional Registor of Port D to 1
//so the light is on
  while (1) {
      PORTD |= (1 << PB7);
      _delay_ms(1000);
      PORTD &= ~(1 << PB7);
      _delay_ms(1000);
  }
  return 0;
}
