#ifndef UPDATE_H
#define UPDATE_H

#include <stdbool.h>
#include "structures.h"

bool is_asteroid_on_screen(struct Asteroid *a);
bool is_bullet_on_screen(struct Bullet *b);
void add_asteroid(struct Asteroid_list *al_head);
void add_boss_bullet(struct Bullet_list *bl_head);
void add_bullet(struct Bullet_list *bl_head);
bool is_colliding_ap(struct Asteroid *a, PlayerClass p);
bool is_colliding_hp(HeartClass h, PlayerClass p);
bool is_colliding_ba(struct Bullet *b, struct Asteroid *a);
bool is_colliding_bp(struct Bullet *b, PlayerClass p);
bool is_colliding_bbs(struct Bullet *b, BossClass bs);
void update_asteroid_position(struct Asteroid *asteroid);
void update_bullet_position(struct Bullet *bullet);
void update(int aux);

#endif