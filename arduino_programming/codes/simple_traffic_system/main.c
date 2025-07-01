#include <avr/io.h>
#include <util/delay.h>

//defining the pin for operation
#define PUSH_SWITCH PB0 
#define RED_LED PD7
#define GREEN_LED PD5
#define YELLOW_LED PD6

int main(int argc, char *argv[])
{ 
  //set data directional register for output pins
  DDRD |= (1 << RED_LED);
  DDRD |= (1 << GREEN_LED);
  DDRD |= (1 << YELLOW_LED);
  //set data directional register for input pins
  DDRB &= ~(1 << PUSH_SWITCH);
  // address the floating pin issue by pulling up the push switch
  PORTB |= (1 << PUSH_SWITCH);
 
  while (1) {//the first loop to involve road-crossingchar
    char flag = 0;
      while (1) {  //second loop for normal traffic mechanism
        if (!(PINB & (1 << PUSH_SWITCH))) {
          flag = 1;
          break;//if push switch is pressed break the loop after finishing the current time frame of the lights
        }
  
        else {
          PORTD |= (1 << RED_LED); //set high 
          _delay_ms(2000);
          PORTD &= ~(1 << RED_LED); //set low
          PORTD |= (1 << GREEN_LED);
          _delay_ms(2000);
          PORTD &= ~(1 << GREEN_LED);
          PORTD |= (1 << YELLOW_LED);
          _delay_ms(1000);
          PORTD &= ~(1 << YELLOW_LED);
        }
      }
    if (flag == 1) {
      PORTD |= (1 << RED_LED); // break after the full cycle
      _delay_ms(5000); //give enough time to cross the road
      }
  }
  
  return 0;
}
