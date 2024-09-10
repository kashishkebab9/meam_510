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
    

    /* insert your hardware initialization here */
    // for(;;){
    //   if (TCNT3 > COMPARE_VAL) { // value for current count to compare 
    //                              // to get desired speed
    //     toggle(PORTC, 6); // toggle led
    //     TCNT3 = 0; //  set to 0 to reset the counter
    //   }

    //     /* insert your main loop code here */
    //     // set_led(TOGGLE);	// switch the led state
    //     // set(PORTB, 7); // turn on pin 7 of port b to HIGH
    //     // _delay_ms(1000 * DUTY_CYCLE);		// This is for long the LED is ON 
    //     //                                 // Therefore, we need to keep it on 
    //     //                                 // For the frequency (in this case 1Hz) 
    //     //                                 // times the duty cycle.

    //     // clear(PORTB, 7); // turn off pin 7 of port b to LOW
    //     // _delay_ms(1000 * (1 - DUTY_CYCLE));    // This is for how long the LED 
    //     //                                        // is OFF. Therefore, we need to
    //     //                                        // keep it off. For the remainder
    //     //                                        // of the frequency(1-DUTY_CYCLE) since 
    //     //                                        freq is 1hz
    // }
    return 0;   /* never reached */
}
