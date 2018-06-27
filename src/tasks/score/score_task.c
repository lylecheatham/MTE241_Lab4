#include "score_task.h"

#include <RTL.h>

#include "led.h"
#include "util.h"

#define GAME_OVER_WAIT_TIME_MS 500

uint8_t score;

uint8_t game_over_flag;

OS_SEM score_change;

uint32_t is_game_over(void);

__task void score_task() {
    uint32_t i;

    // initialize the score to zero
    score = 0;

    // game over flag is 0
    game_over_flag = 0;

    // initialize the LEDs
    init_LEDs();

    // loop
    while (1) {
        // wait until there is a change in score
        os_sem_wait(&score_change, 0);

        // if the game over flag is set
        if (is_game_over()) {
            // we want to flash the LEDs three times
            for (i = 0; i < 3; i++) {
                // put all LEDs on
                display_number(0xFF);

                // wait
                os_dly_wait(GAME_OVER_WAIT_TIME_MS / RTOS_TICK_MS);

                // put score back
                display_number(score);

                // wait
                os_dly_wait(GAME_OVER_WAIT_TIME_MS / RTOS_TICK_MS);
            }
        }

        // else just display the score
        else {
            display_number(score);
        }

        // pass
        os_tsk_pass();
    }
}

err_t score_task_init() {
    err_t err = ERR_NONE;
    int tid;

    // initialize the score_change semaphore to 0
    os_sem_init(score_change, 0);

    // get the tid of the score task
    tid = os_tsk_create(score_task, 1);

    // check the tid of the score task, return an error if it's zero
    if (tid == 0) err = ERR_SCORE_INIT_FAIL;

    // return no error
    return display_error(err);
}

uint8_t score_get() { return score; }

err_t score_increment() {
    err_t err = ERR_NONE;

    // increment the score
    score++;

    // check if score rolled over, and error if so
    if (score == 0) err = ERR_SCORE_OVERFLOW;

    // send to the semaphore
    os_sem_send(&score_change);

    // no error
    return display_error(err);
}

err_t score_reset() {
    err_t err = ERR_NONE;

    // set the score to zero
    score = 0;

    // send to the semaphore
    os_sem_send(&score_change);

    // no error
    return display_error(err);
}

err_t score_game_over() {
    err_t err = ERR_NONE;

    game_over_flag = 1;

    os_sem_send(&score_change);

    return display_error(err);
}

uint32_t is_game_over() {
    if (game_over_flag == 1) {
        game_over_flag = 0;
        return 1;
    }
    return 0;
}
