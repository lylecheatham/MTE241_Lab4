#include "display.h"
#include "GLCD.h"
#include "images.h"


err_t display_init(void) {
    err_t err = ERR_NONE;

    // Initialize the LCD
    if (GLCD_Init() != 0) {
        err = ERR_DISPLAY_FAIL_INIT;
        return display_error(err);
    }

    // Initialize the background
    if (GLCD_SetBackColor(Black) != 0) {
        err = ERR_DISPLAY_FAIL_BACK;
        return display_error(err);
    }

    return display_error(err);
}

err_t display_show(enemy_list* ships_enemy, player_ship* ship_player, laser_list* lasers_enemy, laser_list* lasers_player) {
    err_t err = ERR_NONE;

    // Clear the display
    if (GLCD_Clear(Black) != 0) {
        err = ERR_DISPLAY_FAIL_BACK;
        return display_error(err);
    }

    return display_error(err);
}
