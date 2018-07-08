#include "game_loop_task.h"

#include <RTL.h>

__task void game_loop_task() {
    // loop
    while (1) {
        // pass
        os_tsk_pass();
    }
}

err_t game_loop_task_init() {
    err_t err = ERR_NONE;
    int tid;

    // get the tid of the score task
    tid = os_tsk_create(game_loop_task, 1);

    // check the tid of the score task, return an error if it's zero
    if (tid == 0) err = ERR_GAME_LOOP_INIT_FAIL;

    // return no error
    return display_error(err);
}
