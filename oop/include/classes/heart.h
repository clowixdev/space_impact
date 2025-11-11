#ifndef HEART_H
#define HEART_H

#include <iostream>

#include "entity.h"

using namespace std;

class HeartClass : public EntityClass {
public:
    HeartClass(int heartSize = -1, bool spawn = false, int heartX = -1, int heartY = -1, int heartSpeed = -1) : 
        mIsSpawning(spawn),
        mHeartSpeed(heartSpeed)
    { 
        this->setSize(heartSize);
        this->setPosX(heartX);
        this->setPosY(heartY);
    }

    int getSpeed();
    bool isSpawning();

    void setSpeed(int speed);
    void setSpawning(bool spawn);

    void init();

private:
    bool mIsSpawning;
    int mHeartSpeed;
};

#endif