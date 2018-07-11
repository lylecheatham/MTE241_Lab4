#include "laser.h"
#include <RTL.h>
#include <stddef.h>
#include <stdlib.h>
#include "game_state.h"
#include "score_task.h"


err_t delete_laser(laser* las, laser_list* list);
uint32_t detect_collision(pos_t ship_x, pos_t ship_y, pos_t laser_x, pos_t laser_y);
err_t detect_collision_enemy_ships(laser* las, enemy_list* ships, laser_list* las_list);

err_t reset_lasers(laser_list* enemy_lasers, laser_list* player_lasers) {
    err_t err = ERR_NONE;
    uint32_t index;

    // Seed the random generator with the current time
    // This happens when the user hits the button so it will have entropy
    srand(os_time_get());

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

err_t move_lasers_list_player(laser_list* las, vel_t dy, enemy_list* ships, pos_t lowest) {
    err_t err = ERR_NONE;

    uint32_t index;
    uint32_t count;

    // Perform a nullptr check
    if (las == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    // Increment through the list until we have hit the end or iterated through all the active elements
    for (index = 0, count = 0; index < las->max_length && count < las->num_active; index++) {
        // If it's active
        if (las->list[index].active) {
            // Increment the counter of active elements
            count++;

            // Move the element
            las->list[index].laser_location.y += dy;

            // If off the screen delete the laser
            if (las->list[index].laser_location.y < SCREEN_Y_MIN || las->list[index].laser_location.y > SCREEN_Y_MAX) {
                err = delete_laser(&las->list[index], las);
            }

            // Check if the laser is lower or higher than the lowest enemies
            if (las->list[index].laser_location.y + SHIP_L_Y__2 + LASER_L_Y__2 > lowest) {
                err = detect_collision_enemy_ships(&(las->list[index]), ships, las);
            }
        }
    }

    // Return (with no error)
    return display_error(err);
}

err_t detect_collision_enemy_ships(laser* las, enemy_list* ships, laser_list* las_list) {
    err_t err = ERR_NONE;
    uint32_t index;
    uint32_t count;

    // Nullptr check
    if (las == NULL || ships == NULL || las_list == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    for (index = 0, count = 0; index < ships->max_num_enemies && count < ships->num_alive; index++) {
        if (ships->list[index].active == 1) {
            count++;
            if (detect_collision(0, 0, las->laser_location.x, las->laser_location.y) == 1) {
                // Delete the laser
                err = delete_laser(las, las_list);

                // TODO delete ship

                // Increment the score
                err = score_increment();

                // Return because the laser has been deleted
                return display_error(err);
            }
        }
    }

    return display_error(err);
}

err_t move_lasers_list_enemy(laser_list* las, vel_t dy, player_ship* ship) {
    err_t err = ERR_NONE;

    uint32_t index;
    uint32_t count;

    // Perform a nullptr check
    if (las == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    // Increment through the list until we have hit the end or iterated through all the active elements
    for (index = 0, count = 0; index < las->max_length && count < las->num_active; index++) {
        // If it's active
        if (las->list[index].active) {
            // Increment the counter of active elements
            count++;

            // Move the element
            las->list[index].laser_location.y += dy;

            // If off the screen delete the laser
            if (las->list[index].laser_location.y < SCREEN_Y_MIN || las->list[index].laser_location.y > SCREEN_Y_MAX) {
                err = delete_laser(&las->list[index], las);
            }

            // Check if the laser is lower or higher than the player
            if (las->list[index].laser_location.y - SHIP_L_Y__2 - LASER_L_Y__2 < PLAYER_Y) {
                // Check for a collision with the player
                if (detect_collision(ship->ship_location.x, ship->ship_location.y, las->list[index].laser_location.x, las->list[index].laser_location.y) == 1) {
                    // Game over
                    err = game_state_over();
                }
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

err_t rand_enemy_lasers(laser_list* enemy_lasers, enemy_list* ships) {
    err_t err = ERR_NONE;
    uint32_t rand_uint = 0;
    uint32_t index = 0;
    uint32_t count = 0;


    // Perform a nullptr check
    if (enemy_lasers == NULL || ships == NULL) {
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    if (ships->num_alive == 0) {
        err = ERR_LASER_NONE_ALIVE;
        return display_error(err);
    }


    rand_uint = rand();

    // Only generate a shot half the time
    if (rand_uint % 2 == 1) {
        rand_uint = rand_uint % ships->num_alive;
        for (index = 0, count = 0; index < ships->max_num_enemies && count < ships->num_alive; index++) {
            if (ships->list[index].active == 1) {
                if (count == rand_uint) {
                    err = new_laser(ships->list[index].ship_location.x, ships->list[index].ship_location.y, enemy_lasers);
                    return display_error(err);
                }
                count++;
            }
        }
    }

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
        if (!(ship_x - (SHIP_L_X__2 + LASER_L_X__2) < laser_x)) {
            return 0;
        }
    } else {
        if (!(ship_x + (SHIP_L_X__2 + LASER_L_X__2) > laser_x)) {
            return 0;
        }
    }

    if (ship_y > laser_y) {
        if (!(ship_y - (SHIP_L_Y__2 + LASER_L_Y__2) < laser_y)) {
            return 0;
        }
    } else {
        if (!(ship_y + (SHIP_L_Y__2 + LASER_L_Y__2) > laser_y)) {
            return 0;
        }
    }

    return 1;
}
