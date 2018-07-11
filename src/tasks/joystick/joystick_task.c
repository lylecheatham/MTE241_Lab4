#include "joystick_task.h"

#include <RTL.h>

#include "game_loop_task.h"
#include "joystick.h"

joy_dir_t direction;

__task void joystick_task() {
    // initialize the joystick
    init_joystick();

    // initialize direction to none
    direction = dir_none;

    // loop
    while (1) {
        uint32_t read_dir = get_joystick_dir();

        switch (read_dir) {
            case DIR_NO_INPUT:
                break;

            case DIR_UP:
                direction = dir_up;
                break;

            case DIR_RIGHT:
                direction = dir_right;
                break;

            case DIR_DOWN:
                direction = dir_down;
                break;

            case DIR_LEFT:
                direction = dir_left;
                break;

            default:
                display_error(ERR_JOYSTICK_INVALID_VAL);
                break;
        }

        // Send the event flag to the game loop that a joystick input was read
        set_wait_inputs_joystick();

        // pass
        os_tsk_pass();
    }
}

err_t joystick_task_init() {
    err_t err = ERR_NONE;
    int tid;

    // get the tid of the score task
    tid = os_tsk_create(joystick_task, 1);

    // check the tid of the score task, return an error if it's zero
    if (tid == 0) err = ERR_JOYSTICK_INIT_FAIL;

    // return no error
    return display_error(err);
}

joy_dir_t joystick_dir_get() {
    joy_dir_t dir_to_return = direction;
    direction = dir_none;
    return dir_to_return;
}
