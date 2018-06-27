#define SHIP_L_X 10
#define SHIP_L_Y 10

#define LASER_L_X 2
#define LASER_L_Y 10

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
