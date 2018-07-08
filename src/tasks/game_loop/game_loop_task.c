#include "game_loop_task.h"

#include <RTL.h>

#include "config.h"
#include "joystick_task.h"
#include "laser.h"
#include "ships.h"

__task void game_loop_task() {
    enemy_list ships_enemy;
    player_ship ship_player;
    laser_list lasers_enemy;
    laser_list lasers_player;
    pos_t lowest_enemy;
    joy_dir_t direction;
    vel_t enemy_dx;
    vel_t enemy_dy;

    reset_lasers(&lasers_enemy, &lasers_player);
    reset_ships(&ships_enemy, &ship_player);

    lowest_enemy = 50;
    direction = dir_none;
    enemy_dx = 5;
    enemy_dy = 0;

    display_init();

    // loop
    while (1) {

        // Move the enemies by the calculated dx and dy
        move_enemies(&ships_enemy, enemy_dx, enemy_dy);

        // Get the joystick direction
        direction = joystick_dir_get();

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

        // TODO replace with a wait
        // pass
        os_tsk_pass();
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
