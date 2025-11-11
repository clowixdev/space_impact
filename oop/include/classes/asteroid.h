#ifndef ASTEROID_H
#define ASTEROID_H

#include <iostream>

#include "entity.h"

using namespace std;

class AsteroidClass : public EntityClass {
public:
    AsteroidClass(int asteroidSize = -1, int asteroidX = -1, int asteroidY = -1, int asteroidSpeed = -1) : 
        mAsteroidSpeed(asteroidSpeed)
    { 
        this->setSize(asteroidSize);
        this->setPosX(asteroidX);
        this->setPosY(asteroidY);
    }

    int getSpeed();
    void setSpeed(int speed);

    void init(int size, int speed);

private:
    int mAsteroidSpeed;
};

#endif