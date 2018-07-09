#include "game_state.h"
#include "button_task.h"
#include "game_loop_task.h"
#include "joystick_task.h"
#include "score_task.h"

game_state_e global_game_state;

err_t game_state_over(void) {
    err_t err = ERR_NONE;

    // Check for an invalid state transition
    if (global_game_state != game_running) {
        err = ERR_GAME_STATE_INVALID;
        // Continue running, potentially the user wanted this
    }

    // Change the game state
    global_game_state = game_over;

    // Call the necessary functions
    score_game_over();

    // Return the error status
    return display_error(err);
}

err_t game_state_running(void) {
    err_t err = ERR_NONE;

    // Check for an invalid state transition
    if (global_game_state != game_running) {
        err = ERR_GAME_STATE_INVALID;
        // Continue running, potentially the user wanted this
    }

    // Change the game state
    global_game_state = game_running;

    // Call the necessary functions
    game_loop_start();

    // Return the error status
    return display_error(err);
}

err_t game_state_waiting(void) {
    err_t err = ERR_NONE;

    // Check for an invalid state transition
    if (global_game_state == game_running) {
        err = ERR_GAME_STATE_INVALID;
        // Continue running, potentially the user wanted this
    }

    // Change the game state
    global_game_state = game_waiting;

    // Call the necessary functions
    score_reset();

    game_loop_reset();

    // Return the error status
    return display_error(err);
}

game_state_e game_state_get(void) { return global_game_state; }
