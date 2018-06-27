#include <stdint.h>


#define DIR_NO_INPUT 0
#define DIR_UP 1
#define DIR_RIGHT 2
#define DIR_DOWN 3
#define DIR_LEFT 4

void init_joystick(void);

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
uint32_t get_joystick_dir(void);

// returns a uint32_t number indicating the button state of the joystick.
//
// Parameters:
//   void
//
// Returns:
//   returns uint32_t: a number indicating the joystick press state.
//      0 = not pressed
//      1 = pressed
uint32_t get_joystick_pressed(void);
