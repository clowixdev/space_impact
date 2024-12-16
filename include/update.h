#ifndef UPDATE_H
#define UPDATE_H

#include <stdbool.h>
#include "structures.h"

bool is_asteroid_on_screen(struct Asteroid *a);
bool is_bullet_on_screen(struct Bullet *b);
void add_asteroid(struct Asteroid_list *al_head);
void add_boss_bullet(struct Bullet_list *bl_head);
void add_bullet(struct Bullet_list *bl_head);
bool is_colliding_ap(struct Asteroid *a, struct Player p);
bool is_colliding_hp(struct Heart h, struct Player p);
bool is_colliding_ba(struct Bullet *b, struct Asteroid *a);
bool is_colliding_bp(struct Bullet *b, struct Player p);
bool is_colliding_bbs(struct Bullet *b, struct Boss bs);
void update_asteroid_position(struct Asteroid *asteroid);
void update_bullet_position(struct Bullet *bullet);
void update_boss_state(void);
void player_state_update(void);
void maybe_spawn_heart(struct Asteroid_list *a);
void check_bullet_asteroid_collisions(struct Asteroid_list *asteroids);
void check_asteroid_player_collisions(struct Asteroid_list *current_asteroid);
void update(int aux);

#endif