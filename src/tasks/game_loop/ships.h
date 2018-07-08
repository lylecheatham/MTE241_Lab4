#ifndef SHIPS_H
#define SHIPS_H

#include <stdint.h>

#include "config.h"
#include "error.h"
#include "field.h"

// enemy data type creates an enemy
// includes:
// alive - whether the enemy is currently alive
// enemy_location - the current enemy x and y coordinates
typedef struct enemy {
    uint8_t active;
    location ship_location;
} enemy;

// enemy_list data type creates an array of enemies
// includes:
// num_alive - number of active enemies in the enemy list
// max_num_enemies - the max number of enemies in the game
// enemy_list - a list of enemy data types
typedef struct enemy_list {
    uint8_t num_alive;
    uint8_t max_num_enemies;
    enemy list[SHIPS_MAX_ENEMY];
} enemy_list;

// player data type stores the location of the player
// includes:
// enemy_location - the current player x and y coordinates
// note the y coordinates of the player never change
typedef struct player_ship {
    location ship_location;
} player_ship;

typedef struct ships {
    player_ship player;
    enemy_list enemies;
} ships;


err_t reset_ships(enemy_list* enemies, player_ship* player);
err_t move_enemies(enemy_list* ships, int32_t dx, int32_t dy);
err_t move_player(player_ship* ship, int32_t dx);

#endif /* SHIPS_H */
