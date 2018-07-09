#ifndef GAME_LOOP_TASK_H
#define GAME_LOOP_TASK_H

#include <stdint.h>
#include "error.h"

err_t game_loop_task_init(void);

err_t game_loop_reset(void);

err_t game_loop_start(void);

#endif /* GAME_LOOP_TASK_H */
