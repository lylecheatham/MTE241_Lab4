#include "button.h"

#include <lpc17xx.h>

#include "util.h"

void init_button(void) {}

// returns a uint32_t number indicating button state of the button.
//
// Parameters:
//   void
//
// Returns:
//   returns uint32_t: a number indicating the button state.
//      0 = not pressed
//      1 = pressed
uint32_t get_button_press(void) {
    if (get_bit(LPC_GPIO2->FIOPIN, 10) == 0) {
        return 1;
    } else {
        return 0;
    }
}
