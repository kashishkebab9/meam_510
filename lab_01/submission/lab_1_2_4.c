/* Name: main.c
 * Author: Kashish Garg  
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#define DUTY_CYCLE .50 // duty cycle for toggle PWM val is in %

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
        _delay_ms(1000 * DUTY_CYCLE);		// This is for long the LED is ON 
                                        // Therefore, we need to keep it on 
                                        // For the frequency (in this case 1Hz) 
                                        // times the duty cycle.

        clear(PORTB, 7); // turn off pin 7 of port b to LOW
        _delay_ms(1000 * (1 - DUTY_CYCLE));    // This is for how long the LED 
                                               // is OFF. Therefore, we need to
                                               // keep it off. For the remainder
                                               // of the frequency(1-DUTY_CYCLE)
                                               // since freq is 1hz
    }
    return 0;   /* never reached */
}


