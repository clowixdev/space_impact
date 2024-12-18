#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

struct Player {
    int currentLevel;
    int playerSize;
    int playerY;
    int playerX;
    int playerLives;
    int playerScore;
    bool godMode;
    bool between;
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
    bool between;
};

struct Asteroid {
    int asteroidSize;
    int asteroidY;
    int asteroidX;
    int asteroidSpeed;
    int line;
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
    struct Bullet *bullet;
    struct Bullet_list *next;
};

struct Asteroid_list {
    struct Asteroid *asteroid;
    struct Asteroid_list *next;
};

#endif