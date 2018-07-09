#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "error.h"

typedef enum { game_waiting, game_running, game_over } game_state_e;

err_t game_state_over(void);
err_t game_state_running(void);
err_t game_state_waiting(void);

game_state_e game_state_get(void);


#endif /* GAME_STATE_H */
