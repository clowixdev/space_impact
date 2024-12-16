#ifndef EXTERN_P_H
#define EXTERN_P_H

#include "structures.h"
#include "lists.h"

extern GLuint textures[TEXTURES_AMT+1];

extern bool changed_to_second;
extern bool changed_to_third;
extern bool changed_to_fourth;
extern bool player_is_dead;
extern bool boss_is_dead;
extern bool spawn_asteroids;
extern bool megalovania_is_playing;

extern int boss_delay;

extern struct Player player;
extern struct Boss boss;
extern struct Heart heart;
extern struct Menu main_menu;

extern struct Bullet_list *bullets;
extern struct Bullet_list *boss_bullets;
extern struct Asteroid_list *small_asteroids;
extern struct Asteroid_list *medium_asteroids;
extern struct Asteroid_list *big_asteroids;

extern int frameCountPerSecond; 
extern int frameCount;         
extern double previousTime;

#endif