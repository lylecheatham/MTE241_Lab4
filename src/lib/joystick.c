#include "joystick.h"
#include <lpc17xx.h>

void init_joystick(void) {}

// returns a uint32_t number indicating the direction of the joystick.
// If multiple directions are pressed, the first in the order UP, RIGHT, DOWN,
// LEFT is returned.
//
// Parameters:
//   void
//
// Returns:
//   returns uint32_t: a number indicating the joystick state.
//      0 = no input
//      1 = UP
//      2 = RIGHT
//      3 = DOWN
//      4 = LEFT
uint32_t get_joystick_dir(void) {
    if (get_bit(LPC_GPIO1->FIOPIN, 24) != 0x01) {
        return DIR_UP;
    } else if (get_bit(LPC_GPIO1->FIOPIN, 25) != 0x01) {
        return DIR_RIGHT;
    } else if (get_bit(LPC_GPIO1->FIOPIN, 26) != 0x01) {
        return DIR_DOWN;
    } else if (get_bit(LPC_GPIO1->FIOPIN, 23) != 0x01) {
        return DIR_LEFT;
    }
    return DIR_NO_INPUT;
}

// returns a uint32_t number indicating the button state of the joystick.
//
// Parameters:
//   void
//
// Returns:
//   returns uint32_t: a number indicating the joystick press state.
//      0 = not pressed
//      1 = pressed
uint32_t get_joystick_pressed(void) {
    if (get_bit(LPC_GPIO1->FIOPIN, 20) == 0) {
        return 1;
    }
    return 0;
}
