#include <avr/io.h>


#define LED_PIN PD7
#define PUSH_PIN PD5

int main(int argc, char *argv[])
{
  DDRD |= (1 << LED_PIN); //LED output 

  DDRD &= ~(1 << PUSH_PIN);
  PORTD |= (1 << PUSH_PIN);

  while (1) {
    if (PIND & (1 << PUSH_PIN)) {
      PORTD &= ~(1 << LED_PIN);
    }
    else {
      PORTD |= (1 << LED_PIN);
    }
  }
  


 
  return 0;
}
