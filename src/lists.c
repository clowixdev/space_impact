#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "constants.h"
#include "extern_pointers.h"

struct Asteroid_list* init_asteroid_list_elem(char type) {
    struct Asteroid_list *asteroid_list_elem = (struct Asteroid_list *)calloc(1 ,sizeof(struct Asteroid_list));
    struct Asteroid *asteroid = (struct Asteroid *)calloc(1 ,sizeof(struct Asteroid));

    switch (type)
    {
    case 's':
        asteroid->asteroidSize = SA_SIZE;
        asteroid->spawn = true;
        asteroid->asteroidSpeed = SA_SPEED;
        asteroid->asteroidY = -asteroid->asteroidSize;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
        break;
    case 'm':
        asteroid->asteroidSize = MA_SIZE;
        asteroid->spawn = true;
        asteroid->asteroidSpeed = MA_SPEED;
        asteroid->asteroidY = -asteroid->asteroidSize;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
        break;
    case 'b':
        asteroid->asteroidSize = BA_SIZE;
        asteroid->spawn = true;
        asteroid->asteroidSpeed = BA_SPEED;
        asteroid->asteroidY = -asteroid->asteroidSize;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
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

void add_to_alist() {};

void add_to_blist() {};

void remove_from_alist() {};

void remove_from_blist() {};

void for_asteroid_list() {};

void for_bullet_list() {};