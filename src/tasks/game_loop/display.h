#ifndef DISPLAY_H
#define DISPLAY_H

#include "error.h"
#include "laser.h"
#include "ships.h"

err_t display_init(void);
err_t display_show(enemy_list* ships_enemy, player_ship* ship_player, laser_list* lasers_enemy, laser_list* lasers_player);


#endif /* DISPLAY_H */
