#ifndef UPDATE_H
#define UPDATE_H

#include <stdbool.h>
#include "structures.h"

bool is_asteroid_on_screen(AsteroidClass *a);
bool is_bullet_on_screen(BulletClass *b);
void add_asteroid(struct Asteroid_list *al_head);
void add_boss_bullet(struct Bullet_list *bl_head);
void add_bullet(struct Bullet_list *bl_head);
bool is_colliding_ap(AsteroidClass *a, PlayerClass p);
bool is_colliding_hp(HeartClass h, PlayerClass p);
bool is_colliding_ba(BulletClass *b, AsteroidClass *a);
bool is_colliding_bp(BulletClass *b, PlayerClass p);
bool is_colliding_bbs(BulletClass *b, BossClass bs);
void update_asteroid_position(AsteroidClass *asteroid);
void update_bullet_position(BulletClass *bullet);
void update(int aux);

#endif