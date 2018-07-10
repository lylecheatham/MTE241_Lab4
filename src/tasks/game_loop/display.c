#include "display.h"
#include "GLCD.h"
#include "images.h"

err_t display_init(void) {
    err_t err = ERR_NONE;

    // Initialize the LCD
    GLCD_Init();

    // Initialize the background
    GLCD_SetBackColor(Black);

    // Clear the display
    GLCD_Clear(Black);

    return display_error(err);
}


err_t display_show(enemy_list* ships_enemy, player_ship* ship_player, laser_list* lasers_enemy, laser_list* lasers_player) {
    err_t err = ERR_NONE;
    uint32_t index;

    // Clear the display
    GLCD_Clear(Black);

    // Player ship
    GLCD_Bitmap(ship_player->ship_location.x - SHIP_L_X__2, ship_player->ship_location.y - SHIP_L_Y__2, SHIP_L_X, SHIP_L_Y, (uint8_t*)&bmp_player);

    // Enemy ships
    for (index = 0; index < ships_enemy->max_num_enemies; index++) {
        if (ships_enemy->list[index].active == 1) {
            GLCD_Bitmap(ships_enemy->list[index].ship_location.x - SHIP_L_X__2, ships_enemy->list[index].ship_location.y - SHIP_L_Y__2, SHIP_L_X, SHIP_L_Y,
                        (uint8_t*)&bmp_enemy);
        }
    }

    // Player Lasers
    for (index = 0; index < lasers_player->max_length; index++) {
        if (lasers_player->list[index].active == 1) {
            GLCD_Bitmap(lasers_player->list[index].laser_location.x - LASER_L_X__2, lasers_player->list[index].laser_location.y - LASER_L_Y__2, LASER_L_X,
                        LASER_L_Y, (uint8_t*)&bmp_laser);
        }
    }

    // Enemy Lasers
    for (index = 0; index < lasers_enemy->max_length; index++) {
        if (lasers_enemy->list[index].active == 1) {
            GLCD_Bitmap(lasers_enemy->list[index].laser_location.x - LASER_L_X__2, lasers_enemy->list[index].laser_location.y - LASER_L_Y__2, LASER_L_X,
                        LASER_L_Y, (uint8_t*)&bmp_laser);
        }
    }

    return display_error(err);
}
