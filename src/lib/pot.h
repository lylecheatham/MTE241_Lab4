#ifndef POT_H
#define POT_H

#include <stdint.h>

void init_potentiometer(void);

// returns a uint32_t number indicating the positional value of the
// potentiometer
//
// Parameters:
//   void
//
// Returns:
//   returns uint32_t: a 12 bit number representing the potentiometer position
uint32_t get_potentiometer_position(void);

#endif /* POT_H */
