#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>
#include <stdio.h>

typedef uint8_t err_t;

void error_init(void) { printf("\n"); }

inline err_t display_error(err_t err) {
    if (err == 0) return 0;
    printf("ERROR: %u\n", err);
    return err;
}

enum ERROR {
    ERR_NONE = 0,

    ERR_SCORE_GENERIC = 10,
    ERR_SCORE_INIT_FAIL = 11,
    ERR_SCORE_OVERFLOW = 12,

    ERR_JOYSTICK_GENERIC = 20,
    ERR_JOYSTICK_INIT_FAIL = 21,
    ERR_JOYSTICK_INVALID_VAL = 22,

    ERR_GAME_LOOP_GENERIC = 30,
    ERR_GAME_LOOP_INIT_FAIL = 31,

    ERR_LASER_GENERIC = 80,
    ERR_LASER_NULLPTR = 81,
    ERR_LASER_OVERFLOW = 82,
    ERR_LASER_LOGICAL = 83,
    ERR_LASER_DOUBLE_DELETE = 84,

    ERR_SHIP_GENERIC = 100,
    ERR_SHIP_NULLPTR = 101,
    ERR_SHIP_OUT_BOUNDS = 102,
    ERR_SHIP_PLAYER_OUT_BOUNDS = 103,
    ERR_SHIP_DEAD = 104,
    ERR_SHIP_NONE_ALIVE = 105,

    ERR_DISPLAY_GENERIC = 120,
    ERR_DISPLAY_NULLPTR = 121,
    ERR_DISPLAY_FAIL_INIT = 122,
    ERR_DISPLAY_FAIL_BACK = 123,
    ERR_DISPLAY_FAIL_CLEAR = 124,
    ERR_DISPLAY_FAIL_BMP = 125,

    ERR_GAME_STATE_GENERIC = 130,
    ERR_GAME_STATE_INVALID = 131
};

#endif /* ERROR_H */
