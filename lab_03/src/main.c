/* Name: main.c
 * Author: Kashish Garg  
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include <stdint.h>
#include "m_usb.h"


void setupADC_hardcode(){
  // Setup PF0 and PF1 for ADC
  clear(DDRF, 0);         
  clear(PORTF, 0); 
                   
  clear(DDRF, 1);         
  clear(PORTF, 1); 
  clear(ADMUX, REFS1);
  set(ADMUX, REFS0);

  // clear the following to set the mux pins
  clear(ADCSRA, ADEN);

  // ADC Prescalar
  set(ADCSRA, ADPS2);
  set(ADCSRA, ADPS1);
  set(ADCSRA, ADPS0);

  // Disable Digital Input
  set(DIDR0, ADC0D);
  set(DIDR0, ADC1D);
  

  // re-set this after config
  set(ADCSRA, ADEN);
}

uint16_t readADC(uint8_t channel) {
  // Channel 0 hard code
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

    m_usb_init();
    setupADC_hardcode();
    _clockdivide(0); 


    while(1) {
      uint16_t val_x = readADC(0);
      m_usb_tx_string("V_RX: ");
      m_usb_tx_uint(val_x);
      m_usb_tx_string("\n");

      uint16_t val_y = readADC(1);
      m_usb_tx_string("V_Ry: ");
      m_usb_tx_uint(val_y);
      m_usb_tx_string("\n");

    }

    return 0;   /* never reached */
}

