#include "button_task.h"

#include <RTL.h>

#include "button.h"
#include "game_state.h"

uint32_t pressed;

__task void button_task() {
    // initialize the joystick
    init_button();

    // initialize direction to none
    pressed = 0;

    // loop
    while (1) {
        if(game_state_get() == game_running){
            pressed = pressed | get_button_press();
        } else {
            if(get_button_press() == 1){
                if(game_state_get() == game_waiting){
                    game_state_running();
                } else {
                    game_state_waiting();
                }
                os_dly_wait(10);
            }
        }

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
