#include "laser.h"

err_t new_laser(location* loc, laser_list* list){
    err_t err = ERR_NONE;

    if(list == NULL || loc == NULL){
        err = ERR_LASER_NULLPTR;
        return display_error(err);
    }

    if(list->num_active >= list->max_length){
        err = ERR_LASER_OVERFLOW;
        return display_error(err);
    }

}

err_t new_laser_enemy(location* loc, lasers* las){

}

err_t new_laser_player(location* loc, lasers* las){

}


uint32_t detect_collision(pos_t ship_x, pos_t ship_y, pos_t laser_x,
                          pos_t laser_y) {
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
