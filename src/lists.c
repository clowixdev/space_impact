#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "constants.h"

struct Asteroid_list* init_asteroid_list_elem(char type) {
    struct Asteroid_list *asteroid_list_elem = (struct Asteroid_list *)calloc(1 ,sizeof(struct Asteroid_list));
    struct Asteroid *asteroid = (struct Asteroid *)calloc(1 ,sizeof(struct Asteroid));

    switch (type)
    {
    case 's':
        asteroid->asteroidSize = SA_SIZE;
        asteroid->asteroidSpeed = SA_SPEED;
        asteroid->asteroidY = -asteroid->asteroidSize;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
        asteroid->line = -1;
        break;
    case 'm':
        asteroid->asteroidSize = MA_SIZE;
        asteroid->asteroidSpeed = MA_SPEED;
        asteroid->asteroidY = -asteroid->asteroidSize;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
        asteroid->line = -1;
        break;
    case 'b':
        asteroid->asteroidSize = BA_SIZE;
        asteroid->asteroidSpeed = BA_SPEED;
        asteroid->asteroidY = -asteroid->asteroidSize;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
         asteroid->line = -1;
        break;
    default:
        break;
    }

    asteroid_list_elem->asteroid = asteroid;
    asteroid_list_elem->next = NULL;

    return asteroid_list_elem;
};

struct Bullet_list * init_bullet_list_elem() {
    struct Bullet_list *bullet_list_elem = (struct Bullet_list *)calloc(1 ,sizeof(struct Bullet_list));
    struct Bullet *bullet = (struct Bullet *)calloc(1 ,sizeof(struct Bullet));

    bullet->bulletSize = B_SIZE;
    bullet->bulletSpeed = B_SPEED;
    bullet->bulletY = -bullet->bulletSize;
    bullet->bulletX = -bullet->bulletSize;

    bullet_list_elem->bullet = bullet;
    bullet_list_elem->next = NULL;
    
    return bullet_list_elem;
};


void add_to_alist(struct Asteroid_list *list_head, struct Asteroid_list *a){
    a->next = list_head->next;
    list_head->next = a;
}

void add_to_blist(struct Bullet_list *list_head, struct Bullet_list *b){
    b->next = list_head->next;
    list_head->next = b;
}

struct Asteroid_list * remove_from_alist(struct Asteroid_list *list_head, struct Asteroid *a) {
    if (list_head->asteroid == a) {
        list_head->asteroid->asteroidX = -a->asteroidSize;
        list_head->asteroid->asteroidY = -a->asteroidSize;

        return list_head;
    }

    struct Asteroid_list *temp = list_head->next;
    struct Asteroid_list *prev = list_head;
    while( temp != NULL )
    {
        if (temp->asteroid == a){
            prev->next = temp->next;

            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
    return NULL;
}

struct Bullet_list * remove_from_blist(struct Bullet_list *list_head, struct Bullet *b) {
    if (list_head->bullet == b) {
        list_head->bullet->bulletX = -b->bulletSize;
        list_head->bullet->bulletY = -b->bulletSize;

        return list_head;
    }

    struct Bullet_list *temp = list_head->next;
    struct Bullet_list *prev = list_head;
    while( temp != NULL )
    {
        if (temp->bullet == b){
            prev->next = temp->next;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
};

void for_asteroid_list(struct Asteroid_list **array, struct Asteroid_list *list_head, void (*func)(struct Asteroid_list **list_head, struct Asteroid *asteroid)) {
    struct Asteroid_list *temp = list_head->next;
    while( temp != NULL )
    {
        func(array, temp->asteroid);
        temp = temp->next;
    }
};

void for_bullet_list(struct Bullet_list *list_head, void (*func)(struct Bullet*)) {
    struct Bullet_list *temp = list_head;
    while( temp != NULL )
    {
        func(temp->bullet);
        temp = temp->next;
    }
};