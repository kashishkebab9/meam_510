/* Name: main.c
 * Author: Kashish Garg  
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include <stdint.h>
#define PULSE_RISE 3000
#define PULSE_FLAT 1000
#define PULSE_FALL 6000
#define COMPARE_VAL 6250 // If we set the prescalar to 64, 
                         // the timer is at 250khz
                         // By dividing this clock freq by 20, we count to 
                         // this compare_val

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    set(DDRC,6);        // Allow pin 6 to be output

    // Set PSC 001  for fastest clock:
    clear(TCCR3B, CS32);
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
    uint16_t counter_pulse = 0;
    float duty_cycle = 0;
    float step_rise = 1023.0 / PULSE_RISE;  // Steps for 0.5 seconds to reach 100% duty cycle
    float step_fall = 1023.0 / (10000 - PULSE_FALL);  // Steps for 0.5 seconds to reach 100% duty cycle

    OCR3A = 0;

    while(1) {
        if (counter_pulse < PULSE_RISE) {
          // Brightness climb up
          duty_cycle += step_rise; // Increase the duty cycle gradually
        } 
        else if(counter_pulse > PULSE_FALL) {
          // Brightness descend down
          duty_cycle -= step_fall; // Decrease the duty cycle gradually
        } else {
          duty_cycle = duty_cycle;
        }

        OCR3A = (uint16_t)(duty_cycle); // Set the duty cycle for the LED

        _delay_us(100);  // This delay controls the overall time span for brightness change

        if(counter_pulse >= 10000) {
            counter_pulse = 0;
            duty_cycle = 0; // Reset duty cycle when loop completes
        } else {
            counter_pulse += 1;
        }
    }

    
    return 0;   /* never reached */
}
