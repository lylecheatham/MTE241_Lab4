#ifndef IMAGES_H
#define IMAGES_H

#include "GLCD.h"

uint16_t bmp_player[10][10] = {
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}};

uint16_t bmp_enemy[10][10] = {{Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}};

uint16_t bmp_laser[10][2] = {{White, White}, {White, White}, {White, White}, {White, White}, {White, White},
                         {White, White}, {White, White}, {White, White}, {White, White}, {White, White}};

#endif /* IMAGES_H */
