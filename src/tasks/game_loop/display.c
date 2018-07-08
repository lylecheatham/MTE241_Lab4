#include "display.h"
#include "GLCD.h"
#include "images.h"

err_t display_init(void) {
    err_t err = ERR_NONE;

    // Initialize the LCD
    GLCD_Init();

    // Initialize the background
    GLCD_SetBackColor(Black);

    return display_error(err);
}

err_t display_show(enemy_list* ships_enemy, player_ship* ship_player, laser_list* lasers_enemy, laser_list* lasers_player) {
    err_t err = ERR_NONE;

    // Clear the display
    GLCD_Clear(Black);

    // TODO iterate through and display

    return display_error(err);
}
