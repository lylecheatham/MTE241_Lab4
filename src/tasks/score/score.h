#include <stdint.h>
#include <error.h>

err_t score_task_init();

uint8_t score_get();

err_t score_increment();

err_t score_reset();

err_t score_game_over();
