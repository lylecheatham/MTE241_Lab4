#ifndef   BUTTON_H
#define   BUTTON_H

#include <stdint.h>

// returns a uint32_t number indicating button state of the button.
//
// Parameters:
//   void
//
// Returns:
//   returns uint32_t: a number indicating the button state.
//      0 = not pressed
//      1 = pressed
uint32_t get_button_press(void);

#endif /* BUTTON_H */
