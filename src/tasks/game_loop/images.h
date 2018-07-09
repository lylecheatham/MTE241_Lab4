#ifndef IMAGES_H
#define IMAGES_H

#include "GLCD.h"
#include "config.h"

uint16_t bmp_player[SHIP_L_X][SHIP_L_Y] = {
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}};

uint16_t bmp_enemy[SHIP_L_X][SHIP_L_Y] = {{Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}};

uint16_t bmp_laser[LASER_L_X][LASER_L_Y] = {{White, White, White, White, White, White, White, White, White, White},
                                            {White, White, White, White, White, White, White, White, White, White}};

#endif /* IMAGES_H */
