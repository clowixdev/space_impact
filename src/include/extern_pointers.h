#ifndef EXTERN_P_H
#define EXTERN_P_H

#include "structures.h"

extern GLuint textures[TEXTURES_AMT+1];

extern bool changed_to_second;
extern bool changed_to_third;
extern bool changed_to_fourth;
extern bool player_is_dead;
extern bool boss_is_dead;

extern struct Player player;
extern struct Boss boss;
extern struct Bullet bullet;
extern struct Bullet boss_bullet;
extern struct Heart heart;
extern struct Menu main_menu;
extern struct Asteroid small_asteroid;
extern struct Asteroid medium_asteroid;
extern struct Asteroid big_asteroid;

#endif