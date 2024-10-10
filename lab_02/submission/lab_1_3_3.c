/* Name: main.c
 * Author: Kashish Garg  
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#define DUTY_CYCLE .90 // duty cycle for toggle PWM val is in %
#define COMPARE_VAL 6250 // If we set the prescalar to 64, 
                         // the timer is at 250khz
                         // By dividing this clock freq by 20, we count to 
                         // this compare_val

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    set(DDRC,6);        // Allow pin 6 to be output

    // Set PSC 101  for highest pre-scalar:
    set(TCCR3B, CS32);
    clear(TCCR3B, CS31);
    set(TCCR3B, CS30);
    // 15.625khz

    // Set timer 3 to compare for channel a. Pin C6 is on Channel A, timer 3
    // We want to set this to 1, 0  so that we can use the duty cycle to 
    // ration on and off times
    set(TCCR3A, COM3A1);  
    clear(TCCR3A, COM3A0);  

    // set the waveform generator to mode 7 so we can use the 1023 val and 
    // the OCR3A val
    clear(TCCR3B, WGM33);
    set(TCCR3B, WGM32);
    set(TCCR3A, WGM31);
    set(TCCR3A, WGM30);

    // modulate the compare value to get desired duty cycle
    OCR3A = DUTY_CYCLE * 1023;
    
    return 0;   /* never reached */
}


