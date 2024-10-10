/* Name: main.c
 * Author: Kashish Garg  
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#define COMPARE_VAL 6250 // If we set the prescalar to 64, 
                         // the timer is at 250khz
                         // By dividing this clock freq by 20, we count to 
                         // this compare_val

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    // set_led(ON);			// turn on the on board LED
    // _delay_ms(1000);		// wait 1000 ms when at 16 MHz
    set(DDRC,6);        // Allow pin 6 to be output
    TCCR3B = 0x01;

    // Set PSC to 011 for 64 as prescalar:
    clear(TCCR3B, CS32);
    set(TCCR3B, CS31);
    set(TCCR3B, CS30);

    /* insert your hardware initialization here */
    for(;;){
      if (TCNT3 > COMPARE_VAL) { // value for current count to compare 
                                 // to get desired speed
        toggle(PORTC, 6); // toggle led
        TCNT3 = 0; //  set to 0 to reset the counter
      }
    }
    return 0;   /* never reached */
}
