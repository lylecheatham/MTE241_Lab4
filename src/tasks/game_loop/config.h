#ifndef CONFIG_H
#define CONFIG_H

// Screen size
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 320
#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 240

// sizes of things
#define SHIP_L_X 10
#define SHIP_L_X__2 (SHIP_L_X / 2)
#define SHIP_L_Y 10
#define SHIP_L_Y__2 (SHIP_L_Y / 2)
#define LASER_L_X 2
#define LASER_L_X__2 (LASER_L_X / 2)
#define LASER_L_Y 10
#define LASER_L_Y__2 (LASER_L_Y / 2)

// Speeds of things
#define LASER_SPEED 10
#define PLAYER_SPEED 5

// spacing and initial locations of enemies
#define SHIP_NUM_X 5
#define SHIP_NUM_Y 4
#define SHIP_ENEMY_SPACING_X 20
#define SHIP_ENEMY_SPACING_Y 20
#define SHIP_ENEMY_LEFT_START (SCREEN_X_MIN + 20)
#define SHIP_ENEMY_TOP_START (SCREEN_Y_MAX - 20)

// Initial location of player
#define PLAYER_Y 20
#define PLAYER_X ((SCREEN_X_MAX - SCREEN_X_MIN) / 2)

// Max counts
#define LASER_MAX_ENEMY 10
#define LASER_MAX_PLAYER 10

#define SHIPS_MAX_ENEMY (SHIP_NUM_X * SHIP_NUM_Y)
#define LASER_MAX (LASER_MAX_PLAYER > LASER_MAX_ENEMY ? LASER_MAX_PLAYER : LASER_MAX_ENEMY)

#endif /* CONFIG_H */
