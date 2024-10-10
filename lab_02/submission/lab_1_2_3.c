/* Name: main.c
 * Author: Kashish Garg  
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    // set_led(ON);			// turn on the on board LED
    // _delay_ms(1000);		// wait 1000 ms when at 16 MHz
    set(DDRB,7);        // Allow pin 7 to be output

    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
        // set_led(TOGGLE);	// switch the led state
        set(PORTB, 7); // turn on pin 7 of port b to HIGH
        _delay_ms(1000);		// wait
        clear(PORTB, 7); // turn off pin 7 of port b to LOW
        _delay_ms(1000);    // wait
    }
    return 0;   /* never reached */
}
