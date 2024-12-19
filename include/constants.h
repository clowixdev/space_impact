#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window constants
#define WINDOW_CAPTION "Space Impact - 5131001/30002"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define DRAW_TEXT_LENGTH 15

// rand.c constants
#define RAND_POOL_SIZE 200

// Game canvas constants
#define LINE_COUNT ((WINDOW_HEIGHT - 2 * BORDERS_SIZE) / BA_SIZE)
#define BORDERS_SIZE 75

// Game points constants
#define FOR_SECOND_LEVEL 5
#define FOR_THIRD_LEVEL 15
#define FOR_BOSS_LEVEL 35
#define BOSS_DELAY_VALUE 35

// Game objects constants
#define MAX_ASTEROIDS_IN_BENCH_MODE 100000
#define SA_SPEED 4
#define SA_SIZE 30
#define MA_SPEED 3
#define MA_SIZE 40
#define BA_SPEED 2
#define BA_SIZE 50

#define B_SIZE 10
#define B_SPEED 10

#define PLAYER_SIZE 50
#define PLAYER_LIVES 3
#define PLAYER_SCORE 3
#define PLAYER_START_LEVEL 1
#define PLAYER_MOVE_STEP 10
#define PLAYER_MOVEMENTS_WIDTH 200

#define BOSS_LIVES 10
#define BOSS_SIZE 70

#define HEART_SIZE 30
#define HEART_SPEED 4

// Textures constants
#define TEXTURES_AMT 13
#define PT_FILENAME "../../themes/player.bmp"
#define BT_FILENAME "../../themes/bullet.bmp"
#define BBT_FILENAME "../../themes/boss_bullet.bmp"
#define SAT_FILENAME "../../themes/small_asteroid.bmp"
#define MAT_FILENAME "../../themes/medium_asteroid.bmp"
#define BAT_FILENAME "../../themes/big_asteroid.bmp"
#define BOSST_FILENAME "../../themes/boss.bmp"
#define BGR0_FILENAME "../../themes/background_0heart.bmp"
#define BGR1_FILENAME "../../themes/background_1heart.bmp"
#define BGR2_FILENAME "../../themes/background_2heart.bmp"
#define BGR3_FILENAME "../../themes/background_3heart.bmp"
#define MENUS_FILENAME "../../themes/main_menu_start.bmp"
#define MENUE_FILENAME "../../themes/main_menu_exit.bmp"
#define HEART_FILENAME "../../themes/heart.bmp"

#endif