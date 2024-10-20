/* Name: main.c
 * Author: Kashish Garg  
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include <stdint.h>
#include "m_usb.h"

void setupADC(uint8_t pin) {
  clear(DDRF, pin);         
  clear(PORTF, pin); 
                   
  clear(ADMUX, REFS1);
  set(ADMUX, REFS0);

  // clear the following to set the mux pins
  clear(ADCSRA, ADEN);

  // ADC Prescalar
  set(ADCSRA, ADPS2);
  set(ADCSRA, ADPS1);
  set(ADCSRA, ADPS0);

  // Disable Digital Input
  switch (pin) {
    case 0:
      set(DIDR0, ADC0D);
    case 1:
      set(DIDR0, ADC1D);
    case 2:
      set(DIDR0, ADC2D);
    case 3:
      set(DIDR0, ADC3D);
    case 4:
      set(DIDR0, ADC4D);
    case 5:
      set(DIDR0, ADC5D);
    case 6:
      set(DIDR0, ADC6D);
    case 7:
      set(DIDR0, ADC7D);
  }
  // re-set this after config
  set(ADCSRA, ADEN);
}

uint16_t readADC(uint8_t channel) {
  // Clear the pins
  clear(ADMUX, MUX5);
  clear(ADMUX, MUX2);
  clear(ADMUX, MUX1);
  clear(ADMUX, MUX0);

  ADMUX |= (channel & 0x0F);

  set(ADCSRA, ADSC);

  while (!bit_is_set(ADCSRA, ADIF));

  uint16_t val = ADCL;
  val |= (ADCH << 8);
  return val;
}

int main(void)
{
    //TIMER SETUP
    _clockdivide(0); //set the clock speed to 16Mhz
    set(DDRC,6);        // Allow pin 6 to be output

    // Set PSC 001  for // fastest clock:
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
    clear(TCCR3A, WGM31);
    set(TCCR3A, WGM30);
    OCR3A = 8;
    //TIMER SETUP


    m_usb_init();
    // setupADC_hardcode();
    setupADC(0);
    setupADC(4);
    _clockdivide(0); 


    while(1) {

      uint16_t val_x = readADC(0);
      m_usb_tx_string("V_RX: ");
      m_usb_tx_uint(val_x);
      m_usb_tx_string("\n");

      uint16_t val_y = readADC(4);
      m_usb_tx_string("V_Ry: ");
      m_usb_tx_uint(val_y);
      m_usb_tx_string("\n");

    }

    return 0;   /* never reached */
}

