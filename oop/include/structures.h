#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>
#include "./classes/bullet.h"
#include "./classes/asteroid.h"

struct Player {
    int currentLevel;
    int playerSize;
    int playerY;
    int playerX;
    int playerLives;
    int playerScore;
    bool godMode;
};

struct Boss {
    int bossSize;
    int bossY;
    int bossX;
    int bossLives;
    bool reached_top;
    bool reached_bot;
};

struct Bullet {
    int bulletSize;
    int bulletX;
    int bulletY;
    int bulletSpeed;
};

struct Asteroid {
    int asteroidSize;
    int asteroidY;
    int asteroidX;
    int asteroidSpeed;
};

struct Heart {
    bool spawn;
    int heartSize;
    int heartY;
    int heartX;
    int heartSpeed;
};

struct Menu {
    int option;
};

struct Bullet_list {
    class BulletClass *bullet;
    struct Bullet_list *next;
};

struct Asteroid_list {
    struct AsteroidClass *asteroid;
    struct Asteroid_list *next;
};

#endif