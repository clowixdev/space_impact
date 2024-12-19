#ifndef EXTERN_P_H
#define EXTERN_P_H

#include "constants.h"
#include "structures.h"
#include "lists.h"

extern GLuint textures[TEXTURES_AMT+1];

extern bool changed_to_second;
extern bool changed_to_third;
extern bool changed_to_fourth;
extern bool player_is_dead;
extern bool boss_is_dead;
extern bool spawn_asteroids;
extern bool game_just_started;
extern bool megalovania_is_playing;

extern struct Player player;
extern struct Boss boss;
extern struct Heart heart;
extern struct Menu main_menu;

extern int boss_delay;

extern struct Bullet_list *bullet_array[LINE_COUNT];
extern struct Bullet_list *boss_bullet_array[LINE_COUNT];
extern struct Asteroid_list *small_asteroids_array[LINE_COUNT];
extern struct Asteroid_list *medium_asteroids_array[LINE_COUNT];
extern struct Asteroid_list *big_asteroids_array[LINE_COUNT];

extern struct Bullet_list *bullets;
extern struct Bullet_list *boss_bullets;
extern struct Asteroid_list *small_asteroids;
extern struct Asteroid_list *medium_asteroids;
extern struct Asteroid_list *big_asteroids;

extern int update_count;
extern int bullet_count;

extern int frameCountPerSecond; 
extern int frameCount;         
extern double previousTime;

extern int *random_pool;
extern int random_index;

#endif