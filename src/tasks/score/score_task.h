#ifndef   SCORE_TASK_H
#define   SCORE_TASK_H

#include <stdint.h>
#include "error.h"

err_t score_task_init(void);

uint8_t score_get(void);

err_t score_increment(void);

err_t score_reset(void);

err_t score_game_over(void);

#endif /* SCORE_TASK_H */
