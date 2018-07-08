#include "laser.h"

#include <stddef.h>


err_t new_laser(pos_t x, pos_t y, laser_list* list);
err_t delete_laser(laser* las, laser_list* list);
uint32_t detect_collision(pos_t ship_x, pos_t ship_y, pos_t laser_x, pos_t laser_y);

err_t reset_lasers(laser_list* player_lasers, laser_list* enemy_lasers){
    err_t err = ERR_NONE;
    uint32_t index;

    player_lasers->num_active = 0;
    player_lasers->max_length = LASER_MAX_PLAYER;
    enemy_lasers->num_active = 0;
    enemy_lasers->max_length = LASER_MAX_ENEMY;

    for (index = 0; index < player_lasers->max_length; index++) {
        player_lasers->list[index].active = 0;
        player_lasers->list[index].laser_location.x = 0;
        player_lasers->list[index].laser_location.y = 0;
    }

    for (index = 0; index < enemy_lasers->max_length; index++) {
        enemy_lasers->list[index].active = 0;
        enemy_lasers->list[index].laser_location.x = 0;
        enemy_lasers->list[index].laser_location.y = 0;
    }

    return display_error(err);
}


err_t new_laser(pos_t x, pos_t y, laser_list* list) {
    err_t err = ERR_NONE;
    uint32_t index;

    // Perform a nullptr check
    if (list == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    // Check to see if there is space in the list
    if (list->num_active >= list->max_length) {
        err = ERR_LASER_OVERFLOW;
        return display_error(err);
    }

    // increment through the list
    for (index = 0; index < list->max_length; index++) {
        // find the first inactive entry in the list
        if (list->list[index].active == 0) {
            // Set it active
            list->list[index].active = 1;

            // Set the location
            list->list[index].laser_location.x = x;
            list->list[index].laser_location.y = y;

            // Increment the number of active lasers
            list->num_active++;

            // Return
            return display_error(err);
        }
    }

    // Should not get here, it is a logical error
    err = ERR_LASER_LOGICAL;
    return display_error(err);
}

err_t new_laser_enemy(pos_t x, pos_t y, global_lasers* las) {
    err_t err = ERR_NONE;

    // Perform a nullptr check
    if (las == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    // Call the generic version
    err = new_laser(x, y, &las->enemy_lasers);
    return display_error(err);
}

err_t new_laser_player(pos_t x, pos_t y, global_lasers* las) {
    err_t err = ERR_NONE;

    // Perform a nullptr check
    if (las == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    // Call the generic version
    err = new_laser(x, y, &las->player_lasers);
    return display_error(err);
}

err_t move_lasers_list_player(global_lasers* las, int32_t dy, enemy_list* ships, pos_t lowest) {
    err_t err = ERR_NONE;

    uint32_t index;
    uint32_t count;

    // Perform a nullptr check
    if (las == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    // Increment through the list until we have hit the end or iterated through all the active elements
    for (index = 0, count = 0; index < las->player_lasers.max_length && count < las->player_lasers.num_active; index++) {
        // If it's active
        if (las->player_lasers.list[index].active) {
            // Increment the counter of active elements
            count++;

            // Move the element
            las->player_lasers.list[index].laser_location.y += dy;

            // If off the screen delete the laser
            if (las->enemy_lasers.list[index].laser_location.y < SCREEN_Y_MIN || las->enemy_lasers.list[index].laser_location.y > SCREEN_Y_MAX) {
                err = delete_laser(&las->enemy_lasers.list[index], &las->enemy_lasers);
            }

            // Check if the laser is lower or higher than the lowest or highest enemies, if so
            if (las->player_lasers.list[index].laser_location.y + SHIP_L_Y + LASER_L_Y > lowest) {
                // TODO collision detection
                detect_collision(0, 0, 0, 0);
            }
        }
    }

    // Return (with no error)
    return display_error(err);
}


err_t move_lasers_list_enemy(global_lasers* las, int32_t dy, player_ship* ship) {
    err_t err = ERR_NONE;

    uint32_t index;
    uint32_t count;

    // Perform a nullptr check
    if (las == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    // Increment through the list until we have hit the end or iterated through all the active elements
    for (index = 0, count = 0; index < las->enemy_lasers.max_length && count < las->enemy_lasers.num_active; index++) {
        // If it's active
        if (las->enemy_lasers.list[index].active) {
            // Increment the counter of active elements
            count++;

            // Move the element
            las->enemy_lasers.list[index].laser_location.y += dy;

            // If off the screen delete the laser
            if (las->enemy_lasers.list[index].laser_location.y < SCREEN_Y_MIN || las->enemy_lasers.list[index].laser_location.y > SCREEN_Y_MAX) {
                err = delete_laser(&las->enemy_lasers.list[index], &las->enemy_lasers);
            }

            // Check if the laser is lower or higher than the lowest or highest enemies, if so
            if (las->enemy_lasers.list[index].laser_location.y - SHIP_L_Y - LASER_L_Y < PLAYER_Y) {
                // TODO add collision detection
                detect_collision(0, 0, 0, 0);
            }
        }
    }

    // Return (with no error)
    return display_error(err);
}

err_t delete_laser(laser* las, laser_list* list) {
    err_t err = ERR_NONE;

    // Check to see if it has already been deleted
    if (las->active == 0) {
        err = ERR_LASER_DOUBLE_DELETE;
        return display_error(err);
    }

    // Check for a logical error where the list thinks it is empty but isn't
    if (list->num_active == 0) {
        err = ERR_LASER_LOGICAL;
        return display_error(err);
    }

    // Set the active bit to zero
    las->active = 0;

    // Decrement the active count for the list
    list->num_active--;

    return display_error(err);
}

// Name:
//		enemy_collision_detection
// Functionality:
//		Checks if a laser has collided with any enemy and then deletes both the laser and enemy there is a collision.
// 		The function compares the laser location against all alive enemies and calls collision_detection. If a 1 is
//		returned then the current laser and enemy are deleted, the score is updated and the function returns.
// input:
//		laser* - Takes a laser as input
//		enemy_list* - A list of all in game enemies
// Outputs:
//		err - The error
uint32_t detect_collision(pos_t ship_x, pos_t ship_y, pos_t laser_x, pos_t laser_y) {
    if (ship_x > laser_x) {
        if (!(ship_x - (SHIP_L_X + LASER_L_X) < laser_x)) {
            return 0;
        }
    } else {
        if (!(ship_x + (SHIP_L_X + LASER_L_X) > laser_x)) {
            return 0;
        }
    }

    if (ship_y > laser_y) {
        if (!(ship_y - (SHIP_L_Y + LASER_L_Y) < laser_y)) {
            return 0;
        }
    } else {
        if (!(ship_y + (SHIP_L_Y + LASER_L_Y) > laser_y)) {
            return 0;
        }
    }

    return 1;
}
