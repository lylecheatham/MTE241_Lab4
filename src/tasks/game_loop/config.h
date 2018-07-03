#ifndef CONFIG_H
#define CONFIG_H

#define LASER_MAX_ENEMY 10

#define LASER_MAX_PLAYER 10

#define SHIPS_MAX_ENEMY 20

#define LASER_MAX (LASER_MAX_PLAYER > LASER_MAX_ENEMY ? LASER_MAX_PLAYER : LASER_MAX_ENEMY)

#define SHIPS_MAX SHIPS_MAX_ENEMY

// sizes of things
#define SHIP_L_X 10

#define SHIP_L_Y 10

#define LASER_L_X 2

#define LASER_L_Y 10


#define PLAYER_Y 20

#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 320
#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 180

#endif /* CONFIG_H */
