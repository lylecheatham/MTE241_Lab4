#include "score.h"
#include "led.h"
#include "util.h"
#include <RTX.h>

#define GAME_OVER_WAIT_TIME_MS = 500;

uint8_t score;

uint8_t game_over_flag;

OS_SEM score_change;

size_t is_game_over();

err_t score_task_init(){
    int tid;

    // initialize the score_change semaphore to 0
    os_sem_init(score_change, 0);

    // get the tid of the score task
    tid = os_tsk_create(score_task, 1);

    // check the tid of the score task, return an error if it's zero
    if(tid == 0) return ERR_SCORE_INIT_FAIL;

    // return no error
    return ERR_NONE;
}

__task void score_task() {

    // initialize the score to zero
    score = 0;

    // game over flag is 0
    game_over_flag = 0;

    // initialize the LEDs
    init_LEDs();

    // loop
    while (1) {

        // wait until there is a change in score
        os_sem_wait(&score_change);

        // if the game over flag is set
        if(is_game_over()){

            // we want to flash the LEDs three times
            for(size_t i = 0; i < 3; i++){

                // put all LEDs on
                display_number(0xFF);

                // wait
                os_dly_wait(GAME_OVER_WAIT_TIME_MS/RTOS_TICK_MS);

                // put score back
                display_number(score);

                // wait
                os_dly_wait(GAME_OVER_WAIT_TIME_MS/RTOS_TICK_MS);
            }
        }

        // else just display the score
        else{
            display_number(score);
        }

        // pass
        os_tsk_pass();
    }
}

uint8_t score_get(){
    return score;
}

err_t score_increment(){
    // increment the score
    score++;

    // check if score rolled over, and error if so
    if(score == 0) return ERR_SCORE_OVERFLOW;

    // send to the semaphore
    os_sem_send(&score_change);

    // no error
    return ERR_NONE;
}


err_t score_reset(){
    //set the score to zero
    score = 0;

    // send to the semaphore
    os_sem_send(&score_change);

    // no error
    return ERR_NONE;
}

err_t score_game_over(){
    game_over_flag = 1;

    os_sem_send(&score_change);

    return ERR_NONE;
}


size_t is_game_over(){
	if(game_over_flag == 1){
        game_over_flag = 0;
        return 1;
    }
    return 0;
}
