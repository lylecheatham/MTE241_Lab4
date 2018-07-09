#include "joystick_task.h"

#include <RTL.h>

#include "button.h"

uint32_t pressed;

__task void button_task() {
    // initialize the joystick
    init_button();

    // initialize direction to none
    pressed = 0;

    // loop
    while (1) {
        pressed = pressed | get_button_press();

        // pass
        os_tsk_pass();
    }
}

err_t button_task_init() {
    err_t err = ERR_NONE;
    int tid;

    // get the tid of the score task
    tid = os_tsk_create(button_task, 1);

    // check the tid of the score task, return an error if it's zero
    if (tid == 0) err = ERR_JOYSTICK_INIT_FAIL;

    // return no error
    return display_error(err);
}

uint32_t button_press_get() {
    uint32_t press_to_return = pressed;
    pressed = 0;
    return press_to_return;
}
