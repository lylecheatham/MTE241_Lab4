#ifndef LASER_H
#define LASER_H

#include <stdint.h>

#include "config.h"
#include "error.h"
#include "field.h"

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

typedef struct global_lasers {
    laser_list player_lasers;
    laser_list enemy_lasers;
} global_lasers;


err_t reset_lasers();


err_t new_laser(pos_t x, pos_t y, laser_list* list);

err_t new_laser_enemy(pos_t x, pos_t y, global_lasers* las);
err_t new_laser_player(pos_t x, pos_t y, global_lasers* las);

err_t move_lasers(global_lasers* las);
err_t move_lasers_list(laser_list* list, int32_t dx, int32_t dy);

err_t delete_laser(laser* las, laser_list* list);

uint32_t detect_collision(pos_t ship_x, pos_t ship_y, pos_t laser_x, pos_t laser_y);

#endif /* LASER_H */
