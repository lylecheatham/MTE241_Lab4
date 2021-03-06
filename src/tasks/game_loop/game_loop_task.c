#include "game_loop_task.h"

#include <RTL.h>

#include "button_task.h"
#include "config.h"
#include "display.h"
#include "game_state.h"
#include "joystick_task.h"
#include "laser.h"
#include "ships.h"

err_t wait_inputs(void);
err_t clear_inputs(void);

uint32_t global_game_loop_reset_flag = 0;
uint32_t global_game_loop_run_flag = 0;

OS_TID game_loop_tid = 0;

enemy_list ships_enemy;
player_ship ship_player;
laser_list lasers_enemy;
laser_list lasers_player;

__task void game_loop_task() {
    // Structures for the game function


    // Variables to be held loop to loop
    pos_t lowest_enemy;
    joy_dir_t direction;
    uint32_t button_pressed;
    pos_t enemy_x;
    vel_t enemy_dx;
    vel_t enemy_dy;


    // Set wait time to 5 ticks = 50ms
    os_itv_set(50);

    // Initialize the game state
    game_state_waiting();

    while (1) {
        // Initialize the game function structures
        reset_lasers(&lasers_enemy, &lasers_player);
        reset_ships(&ships_enemy, &ship_player);

        // Initialize the variables
        // lowest enemy is the (top of the enemy array) - (number of ships in y) * (spacing of ships in y)
        lowest_enemy = SHIP_ENEMY_TOP_START - SHIP_NUM_Y * SHIP_ENEMY_SPACING_Y;
        direction = dir_none;
        button_pressed = 0;
        enemy_dx = 5;
        enemy_dy = 0;
        enemy_x = SHIP_EDGE_BUFFER;

        // Wait for the run flag to be set
        while (global_game_loop_run_flag == 0) {
            os_itv_wait();
        }

        // Clear the run and the reset flag
        global_game_loop_run_flag = 0;
        global_game_loop_reset_flag = 0;

        // Run until the reset flag is set
        while (global_game_loop_reset_flag == 0) {
            // Wait for the inputs from joystick and button
            wait_inputs();

            enemy_x += enemy_dx;
            enemy_dy = 0;

            // If we get to positive end of the screen
            if (enemy_x > SCREEN_X_MAX - SHIP_EDGE_BUFFER - (SHIP_ENEMY_SPACING_X * (SHIP_NUM_X - 1))) {
                // Reverse direction
                enemy_dx = -5;

                // undo the erroneous increment and decrement
                enemy_x += 2 * enemy_dx;

                // set the y velocity to be negative
                enemy_dy = -5;

                // If we get to the negative end of the screen
            } else if (enemy_x < SCREEN_X_MIN + SHIP_EDGE_BUFFER) {
                // Reverse direction
                enemy_dx = 5;

                // undo the erroneous increment and decrement
                enemy_x += 2 * enemy_dx;

                // set the y velocity to be negative
                enemy_dy = -5;
            }

            lowest_enemy += enemy_dy;

            if (lowest_enemy < PLAYER_Y) {
                game_state_over();
            }

            // Move the enemies by the calculated dx and dy
            move_enemies(&ships_enemy, enemy_dx, enemy_dy);

            // Get the joystick direction
            direction = joystick_dir_get();

            // Get the button status
            button_pressed = button_press_get();

            // Clear the input flags so that we guarantee that we get fresh data next time
            clear_inputs();

            // Move the player accordingly
            if (direction == dir_left) {
                move_player(&ship_player, PLAYER_SPEED);
            } else if (direction == dir_right) {
                move_player(&ship_player, -PLAYER_SPEED);
            }

            // On button press shoot a laser from the player
            if (button_pressed == 1) {
                new_laser(ship_player.ship_location.x, ship_player.ship_location.y, &lasers_player);
            }

            // If there are no ships left, reset the board but don't reset the score
            if(ships_enemy.num_alive == 0){
                reset_ships(&ships_enemy, &ship_player);
            }

            // Move the player lasers
            move_lasers_list_player(&lasers_player, LASER_SPEED, &ships_enemy, lowest_enemy);

            // Move the enemy lasers
            move_lasers_list_enemy(&lasers_enemy, -LASER_SPEED, &ship_player);

            // Generate random enemy lasers
            rand_enemy_lasers(&lasers_enemy, &ships_enemy);

            // Redraw the display
            display_show(&ships_enemy, &ship_player, &lasers_enemy, &lasers_player);

            // wait until the next 50ms uptime
            os_itv_wait();
        }

        // Clear the reset flag
        global_game_loop_reset_flag = 0;
    }
}

err_t game_loop_reset() {
    err_t err = ERR_NONE;

    global_game_loop_reset_flag = 1;

    return display_error(err);
}

err_t game_loop_start() {
    err_t err = ERR_NONE;

    global_game_loop_run_flag = 1;

    return display_error(err);
}

err_t game_loop_task_init() {
    err_t err = ERR_NONE;
    OS_TID tid;

    // get the tid of the score task
    tid = os_tsk_create(game_loop_task, 3);

    // check the tid of the score task, return an error if it's zero
    if (tid == 0) {
        err = ERR_GAME_LOOP_INIT_FAIL;
    } else {
        game_loop_tid = tid;
    }

    return display_error(err);
}

err_t wait_inputs(void) {
    err_t err = ERR_NONE;

    // Check for valid TID
    if (game_loop_tid == 0) {
        err = ERR_GAME_LOOP_TID;
        return display_error(err);
    }

    // Wait for the button and joystick flags to be set so that we can get fresh inputs
    os_evt_wait_and(0x03, 5);

    return display_error(err);
}

err_t clear_inputs(void) {
    err_t err = ERR_NONE;

    // Check for valid TID
    if (game_loop_tid == 0) {
        err = ERR_GAME_LOOP_TID;
        return display_error(err);
    }

    // Clear the button and joystick flag
    os_evt_clr(0x03, game_loop_tid);

    return display_error(err);
}

err_t set_wait_inputs_joystick(void) {
    err_t err = ERR_NONE;

    // Check for valid TID
    if (game_loop_tid == 0) {
        err = ERR_GAME_LOOP_TID;
        return display_error(err);
    }

    // Set the joystick flag to indicate it has been read
    os_evt_set(0x01, game_loop_tid);

    return display_error(err);
}

err_t set_wait_inputs_button(void) {
    err_t err = ERR_NONE;

    // Check for valid TID
    if (game_loop_tid == 0) {
        err = ERR_GAME_LOOP_TID;
        return display_error(err);
    }

    // Set the button flag to indicate it has been read
    os_evt_set(0x02, game_loop_tid);

    return display_error(err);
}
