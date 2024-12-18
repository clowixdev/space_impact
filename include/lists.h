#ifndef LISTS_H
#define LISTS_H

#include "structures.h"

struct Asteroid_list * init_asteroid_list_elem(char type);
struct Bullet_list * init_bullet_list_elem();

void add_to_alist(struct Asteroid_list *list_head, struct Asteroid_list *a);
void add_to_blist(struct Bullet_list *list_head, struct Bullet_list *b);

struct Asteroid_list * remove_from_alist(struct Asteroid_list *list_head, struct Asteroid *a);
struct Bullet_list * remove_from_blist(struct Bullet_list *list_head, struct Bullet *b);

void for_asteroid_list(struct Asteroid_list ** array, struct Asteroid_list *list_head, void (*func)(struct Asteroid_list **list_head, struct Asteroid *asteroid));
void for_bullet_list(struct Bullet_list *list_head, void (*func)(struct Bullet*));

#endif