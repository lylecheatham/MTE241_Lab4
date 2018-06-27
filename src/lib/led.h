#ifndef   LED_H
#define   LED_H

#include <stdint.h>

void init_LEDs(void);

// Displays a number using the LEDs on the bottom of the board
//
// Parameters:
//   uint8_t num: The number to display
//
// Returns:
//   void
void display_number(uint8_t num);

#endif /* LED_H */
