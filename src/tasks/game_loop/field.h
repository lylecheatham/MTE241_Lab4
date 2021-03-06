#ifndef FIELD_H
#define FIELD_H

#include <stdint.h>

typedef int32_t pos_t;
typedef int32_t vel_t;

// location data type stores the current x and y coordinates of an object
//
// includes;
// x_center - the x coordinate of the center of the object
// y_center - the y coordinate of the center of the object
typedef struct location {
    pos_t x;
    pos_t y;
} location;

#endif /* FIELD_H */
