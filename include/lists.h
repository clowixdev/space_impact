#ifndef LISTS_H
#define LISTS_H

#include "structures.h"

struct Bullet_list {
    struct Bullet *bullet;
    struct Bullet_list *next;
};

struct Asteroid_list {
    struct Asteroid *asteroid;
    struct Asteroid_list *next;
};

struct Asteroid_list * init_asteroid_list_elem() {};
struct Bullet_list * init_bullet_list_elem() {};

void remove_from_alist() {};
void remove_from_blist() {};

void for_asteroid_list() {};
void for_bullet_list() {};

#endif