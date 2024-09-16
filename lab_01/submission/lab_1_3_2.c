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
    set(DDRC,6);        // Allow pin 6 to be output
    TCCR3B = 0x01;

    // Set PSC to 100 for a different pre-scalar:
    set(TCCR3B, CS32);
    clear(TCCR3B, CS31);
    clear(TCCR3B, CS30);

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

