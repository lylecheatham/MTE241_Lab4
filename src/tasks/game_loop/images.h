#ifndef IMAGES_H
#define IMAGES_H

#include "GLCD.h"

uint16_t player[10][10] = {
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green},
    {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}, {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green}};

uint16_t enemy[10][10] = {{Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red},
                          {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}, {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red}};

uint16_t laser[2][10] = {{White, White}, {White, White}, {White, White}, {White, White}, {White, White},
                         {White, White}, {White, White}, {White, White}, {White, White}, {White, White}};

#endif /* IMAGES_H */
