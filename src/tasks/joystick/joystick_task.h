#ifndef JOYSTICK_TASK_H
#define JOYSTICK_TASK_H

#include <stdint.h>
#include "error.h"

typedef enum{dir_left, dir_right, dir_up, dir_down, dir_none} joy_dir_t;

err_t joystick_task_init();

joy_dir_t joystick_dir_get();

#endif /* JOYSTICK_TASK_H */

