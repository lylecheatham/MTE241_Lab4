#include "game_loop_task.h"

#include <RTL.h>

#include "button_task.h"
#include "config.h"
#include "display.h"
#include "joystick_task.h"
#include "laser.h"
#include "ships.h"

__task void game_loop_task() {
    // Structures for the game function
    enemy_list ships_enemy;
    player_ship ship_player;
    laser_list lasers_enemy;
    laser_list lasers_player;


    // Variables to be held loop to loop
    pos_t lowest_enemy;
    joy_dir_t direction;
    uint32_t button_pressed;
    vel_t enemy_dx;
    vel_t enemy_dy;

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

    // Initialize the display
    display_init();

    // Set wait time to 5 ticks = 50ms
    os_itv_set(5);

    // loop
    while (1) {
        // TODO calculate dx and dy

        // Move the enemies by the calculated dx and dy
        move_enemies(&ships_enemy, enemy_dx, enemy_dy);

        // Get the joystick direction
        direction = joystick_dir_get();

        // Get the button status
        button_pressed = button_press_get();

        // Move the player accordingly
        if (direction == dir_left) {
            move_player(&ship_player, -PLAYER_SPEED);
        } else if (direction == dir_right) {
            move_player(&ship_player, PLAYER_SPEED);
        }

        // Move the player lasers
        move_lasers_list_player(&lasers_player, LASER_SPEED, &ships_enemy, lowest_enemy);

        // Move the enemy lasers
        move_lasers_list_enemy(&lasers_enemy, -LASER_SPEED, &ship_player);

        // Redraw the display
        display_show(&ships_enemy, &ship_player, &lasers_enemy, &lasers_player);

        // wait until the next 50ms uptime
        os_itv_wait();
    }
}

err_t game_loop_task_init() {
    err_t err = ERR_NONE;
    int tid;

    // get the tid of the score task
    tid = os_tsk_create(game_loop_task, 1);

    // check the tid of the score task, return an error if it's zero
    if (tid == 0) err = ERR_GAME_LOOP_INIT_FAIL;

    // return no error
    return display_error(err);
}
