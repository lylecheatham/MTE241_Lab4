#include <RTL.h>
#include <stdint.h>
#include <stdio.h>
#include "GLCD.h"
#include "pot.h"
#include "led.h"
#include "util.h"
#include "button.h"
#include "joystick.h"
#include "score_task.h"

__task void test_score() {
    uint32_t i;

    while (1) {
			score_reset();
				for(i = 0; i < 255; i++){
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
    // Call score task init. The score task will creates all other tasks
		score_task_init();
	os_tsk_create(test_score, 1);

    // Delete task because no longer needed
    os_tsk_delete_self();

    // Belt and suspenders
    while (1) {
        os_tsk_pass();
    }
}



int main(void) {
    
    printf("asdf");  // Initialize the UART before RTOS starts

    os_sys_init(start_tasks);

    while (1)
        ;
}
