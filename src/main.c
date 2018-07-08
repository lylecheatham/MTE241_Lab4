#include <RTL.h>
#include <stdint.h>
#include <stdio.h>
#include "GLCD.h"
#include "button.h"
#include "joystick.h"
#include "led.h"
#include "pot.h"
#include "score_task.h"
#include "util.h"

__task void test_score() {
    uint32_t i;

    while (1) {
        score_reset();
        for (i = 0; i < 255; i++) {
            score_increment();
            os_dly_wait(3);
        }
        printf("SCORE: %u\n", score_get());
        score_increment();
        score_increment();
        printf("SCORE: %u\n", score_get());
        score_reset();
        printf("SCORE: %u\n", score_get());
        score_increment();
        score_game_over();
        os_dly_wait(1000);
    }
}
__task void start_tasks() {
    // Initialize the score task
    score_task_init();

    // Initialize the joystick task
    joystick_task_init();

    // Initialize the button task
    button_task_init();

    // Initialize the game loop task
    game_loop_task_init();

#ifdef TEST_CDE
    os_tsk_create(test_score, 1);
#endif

    // Delete task because no longer needed
    os_tsk_delete_self();

    // Belt and suspenders
    while (1) {
        os_tsk_pass();
    }
}

int main(void) {
    // Initialize the UART before RTOS starts
    printf("\n");

    os_sys_init(start_tasks);

    while (1)
        ;
}
