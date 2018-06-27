#include <lpc17xx.h>
#include "pot.h"

void init_potentiometer(void) {
    LPC_PINCON->PINSEL1 &= ~(0x03 << 18);
    LPC_PINCON->PINSEL1 |= (0x01 << 18);

    LPC_SC->PCONP |= (1 << 12);  // Turn on the ADC peripheral

    LPC_ADC->ADCR = (1 << 2) |  // Select AD0.2 pin
                    (4 << 8) |  // ADC clock is 25MHz/5
                    (1 << 21);  // enable ADC
}


// returns a uint32_t number indicating the positional value of the
// potentiometer
//
// Parameters:
//   void
//
// Returns:
//   returns uint32_t: a 12 bit number representing the potentiometer position
uint32_t get_potentiometer_position(void) {
    LPC_ADC->ADCR |= (1 << 24);  // Start an ADC read

    while (get_bit(LPC_ADC->ADGDR, 31) == 0) {
        // Block
    }

    return (LPC_ADC->ADGDR & 0xFFF0) >> 4;
}
