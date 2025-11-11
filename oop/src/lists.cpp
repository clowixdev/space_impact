#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "constants.h"

struct Asteroid_list* init_asteroid_list_elem(char type) {
    struct Asteroid_list *asteroid_list_elem = (struct Asteroid_list *)calloc(1, sizeof(struct Asteroid_list));
    class AsteroidClass *asteroid_clw = new AsteroidClass();

    switch (type)
    {
    case 's':
        asteroid_clw->init(SA_SIZE, SA_SPEED);
        break;
    case 'm':
        asteroid_clw->init(MA_SIZE, MA_SPEED);
        break;
    case 'b':
        asteroid_clw->init(BA_SIZE, BA_SPEED);
        break;
    default:
        break;
    }

    asteroid_list_elem->asteroid = asteroid_clw;
    asteroid_list_elem->next = NULL;

    return asteroid_list_elem;
};

struct Bullet_list * init_bullet_list_elem() {
    struct Bullet_list *bullet_list_elem = (struct Bullet_list *)calloc(1, sizeof(struct Bullet_list));
    class BulletClass *bullet_clw = new BulletClass();

    bullet_clw->init();

    bullet_list_elem->bullet = bullet_clw;
    bullet_list_elem->next = NULL;
    
    return bullet_list_elem;
};

void remove_from_alist(struct Asteroid_list *list_head, AsteroidClass *a) {
    if (list_head->asteroid == a) {
        list_head->asteroid->setPosX(-a->getSize());
        list_head->asteroid->setPosY(-a->getSize());

        return;
    }

    struct Asteroid_list *temp = list_head->next;
    struct Asteroid_list *prev = list_head;
    while( temp !=NULL )
    {
        if (temp->asteroid == a){
            prev->next = temp->next;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
};

void remove_from_blist(struct Bullet_list *list_head, BulletClass *b) {
    if (list_head->bullet == b) {
        list_head->bullet->setPosX(-b->getSize());
        list_head->bullet->setPosY(-b->getSize());

        return;
    }

    struct Bullet_list *temp = list_head->next;
    struct Bullet_list *prev = list_head;
    while( temp != NULL )
    {
        if (temp->bullet == b){
            prev->next = temp->next;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
};

void for_asteroid_list(struct Asteroid_list *list_head, void (*func)(AsteroidClass*)) {
    struct Asteroid_list *temp = list_head;
    while( temp != NULL )
    {
        func(temp->asteroid);
        temp = temp->next;
    }
};

void for_bullet_list(struct Bullet_list *list_head, void (*func)(BulletClass*)) {
    struct Bullet_list *temp = list_head;
    while( temp != NULL )
    {
        func(temp->bullet);
        temp = temp->next;
    }
};