#ifndef LASER_H
#define LASER_H

#include <stdint.h>

#include "config.h"
#include "error.h"
#include "field.h"
#include "ships.h"

// laser data type creates a laser
//
// includes:
// laser_location - the current center location of the laser
// active - whether the laser is currently active
typedef struct laser {
    location laser_location;
    uint8_t active;
} laser;

// laser_list data type creates an array of lasers
//
// includes:
// num_active - number of active lasers in the laser list
// max_length - the max length of the laser data type list
// laser_list - a list of laser data types
typedef struct laser_list {
    uint8_t num_active;
    uint8_t max_length;
    laser list[LASER_MAX];
} laser_list;


err_t reset_lasers(laser_list* enemy_lasers, laser_list* player_lasers);

err_t new_laser(pos_t x, pos_t y, laser_list* list);

err_t move_lasers_list_player(laser_list* las, vel_t dy, enemy_list* ships, pos_t lowest);
err_t move_lasers_list_enemy(laser_list* las, vel_t dy, player_ship* ship);

err_t rand_enemy_lasers(laser_list* enemy_lasers, enemy_list* ships);


#endif /* LASER_H */
