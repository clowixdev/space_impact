#ifndef UPDATE_H
#define UPDATE_H

void update(int);
bool is_asteroid_on_screen(struct Asteroid *);
bool is_bullet_on_screen(struct Bullet *);
void add_big_asteroid();
void add_medium_asteroid();
void add_small_asteroid();
void add_boss_bullet();
void add_bullet();


#endif