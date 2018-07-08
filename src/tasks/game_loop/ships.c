#include "ships.h"

err_t move_enemies(enemy_list* ships, int32_t dx, int32_t dy) {
    err_t err = ERR_NONE;
    err_t temp_err = ERR_NONE;
    uint32_t index;
    uint32_t count;

    // Check if there are any enemies alive
    if (ships->num_alive == 0) {
        err = ERR_SHIP_NONE_ALIVE;
        return display_error(err);
    }

    for (index = 0, count = 0; index < ships->max_num_enemies && count < ships->num_alive; index++) {
        if (ships->list[index].active == 1) {
            // Increment the count of alive ships indexed
            count++;

            // Move the enemy and store the error
            temp_err = move_enemy(&ships->list[index], dx, dy);

            // If the enemy is out of bounds continue but store the error for later return
            // If we get a different error, break out and return that
            if (temp_err == ERR_SHIP_OUT_BOUNDS) {
                err = ERR_SHIP_OUT_BOUNDS;
            } else if (temp_err != ERR_NONE) {
                err = temp_err;
                return display_error(err);
            }
        }
    }

    return display_error(err);
}

err_t move_enemy(enemy* ship, int32_t dx, int32_t dy) {
    err_t err = ERR_NONE;

    // Check to ensure the enemies are not dead
    if (ship->active == 0) {
        err = ERR_SHIP_DEAD;
        return display_error(err);
    }

    // Check to ensure ships are within the bounds of the screen
    if (ship->ship_location.x + dx > SCREEN_X_MAX || ship->ship_location.y + dy > SCREEN_Y_MAX || ship->ship_location.x + dx < SCREEN_X_MIN ||
        ship->ship_location.y + dy < SCREEN_Y_MIN) {
        err = ERR_SHIP_OUT_BOUNDS;
        return display_error(err);
    }

    // Move the enemy by dx and dy
    ship->ship_location.x += dx;
    ship->ship_location.y += dy;

    return display_error(err);
}


err_t move_player(player_ship* ship, int32_t dx) {
    err_t err = ERR_NONE;

    // Check to ensure player is within the bounds of the screen
    if (ship->ship_location.x + dx > SCREEN_X_MAX || ship->ship_location.x + dx < SCREEN_X_MIN) {
        err = ERR_SHIP_PLAYER_OUT_BOUNDS;
        return display_error(err);
    }

    // Move the player by dx
    ship->ship_location.x += dx;

    return display_error(err);
}
