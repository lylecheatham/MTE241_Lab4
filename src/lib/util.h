#include <stdint.h>

#define RTOS_TICK_MILLIS 10

// gets a bit from a uint32_t
//
// Parameters:
//   uint32_t val: the input value
//   uint8_t bit: The requested bit
//
// Returns:
//   returns uint32_t: the requested value in the LSB, everything else zeroed
uint32_t get_bit(uint32_t val, uint8_t bit);
