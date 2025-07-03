#include <avr/io.h>     // Provides definitions for AVR registers (DDRB, PORTB, etc.)
#include <util/delay.h> // Provides the _delay_ms() function for precise delays

int main(void) {
    // Set Pin PB5 (corresponding to Arduino Digital Pin 13) as an OUTPUT.
    // DDRB is the Data Direction Register for Port B.
    // By setting the 5th bit (PB5) to 1, we configure it as an output.
    // The '|=' operator performs a bitwise OR assignment, setting the bit without affecting others.
    DDRB |= (1 << DDB5); // DDB5 is the bit position for PB5

    // The main program loop. This runs continuously, similar to Arduino's loop() function.
    while (1) {
        // Set Pin PB5 HIGH (turn the LED ON).
        // PORTB is the Port B Output Register. Setting its 5th bit to 1 outputs HIGH.
        PORTD ^= (1 << PD5);
        _delay_ms(1000);
// Wait for 1000 milliseconds (1 second)
    }

    return 0; // In embedded systems, this line is typically never reached as the loop runs indefinitely.
}
