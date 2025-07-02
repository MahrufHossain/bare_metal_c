#include <avr/io.h>
#include <util/delay.h>

//defining the pin for operation
#define PUSH_SWITCH PB0
#define RED_LED PD7
#define GREEN_LED PD5
#define YELLOW_LED PD6

typedef enum {
  STATE_GREEN_TRAFFIC,
  STATE_RED_TRAFFIC,
  STATE_YELLOW_TRAFFIC,
  STATE_PEDESTRIAN_CROSS
} TrafficLightState;

TrafficLightState current_state = STATE_RED_TRAFFIC;

volatile uint8_t pedestrian_requested = 0;

void setup() {
  DDRD |= ((1 << RED_LED) | (1 << GREEN_LED) | (1 << YELLOW_LED));
  //set data directional register for input pins
  DDRB &= ~(1 << PUSH_SWITCH);
  // address the floating pin issue by pulling up the push switch
  PORTB |= (1 << PUSH_SWITCH);

}
int main(int argc, char *argv[])
{ 
  //set data directional register for output pins
  setup();

  while (1) {         
    if (!(PINB & (1 << PUSH_SWITCH))) {
      _delay_ms(50);
      if (!(PINB & (1 << PUSH_SWITCH))) {
        pedestrian_requested = 1;
      }
    }

    switch (current_state) {
      case STATE_GREEN_TRAFFIC:
        PORTD |= (1 << GREEN_LED);
        PORTD &= ~((1 << RED_LED) | (1 << YELLOW_LED));
        _delay_ms(2000);


        current_state = STATE_YELLOW_TRAFFIC;
        break;
      
      case STATE_YELLOW_TRAFFIC:
        PORTD |= (1 << YELLOW_LED);
        PORTD &= ~((1 << RED_LED) | (1 << GREEN_LED));
        _delay_ms(1000);

        current_state = STATE_RED_TRAFFIC;
        break;
      
      case STATE_RED_TRAFFIC:
        PORTD |= (1 << RED_LED);
        PORTD &= ~((1 << GREEN_LED) | (1 << YELLOW_LED));
        _delay_ms(2000);

        if (pedestrian_requested == 1) {
          current_state = STATE_PEDESTRIAN_CROSS;
          pedestrian_requested = 0;
        }
        else {
          current_state = STATE_GREEN_TRAFFIC;

        }
        break;
      

      case STATE_PEDESTRIAN_CROSS:
        PORTD |= (1 << RED_LED);
        PORTD &= ~((1 << GREEN_LED) | (1 << YELLOW_LED));

        _delay_ms(5000);
        current_state = STATE_GREEN_TRAFFIC;
        break;    
    }
  }
  
  return 0;
}
