#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include "entity.h"

using namespace std;

class BulletClass : public EntityClass {
public:
    BulletClass(int bulletSize = -1, int bulletX = -1, int bulletY = -1, int bulletSpeed = -1) : 
        mBulletSpeed(bulletSpeed)
    { 
        this->setSize(bulletSize);
        this->setPosX(bulletX);
        this->setPosY(bulletY);
    }

    int getSpeed();
    void setSpeed(int speed);

    void init();

private:
    int mBulletSpeed;
};

#endif