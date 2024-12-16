#ifndef LISTS_H
#define LISTS_H

#include "structures.h"

struct Asteroid_list * init_asteroid_list_elem(char type);
struct Bullet_list * init_bullet_list_elem();

void remove_from_alist(struct Asteroid_list *list_head, struct Asteroid *a);
void remove_from_blist(struct Bullet_list *list_head, struct Bullet *b);

void for_asteroid_list(struct Asteroid_list *list_head, void (*func)(struct Asteroid*));
void for_bullet_list(struct Bullet_list *list_head, void (*func)(struct Bullet*));

#endif