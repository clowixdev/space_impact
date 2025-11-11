#include <iostream>
#include <fstream>

#include "classes/bullet.h"
#include "constants.h"

int BulletClass::getSpeed() {
    return this->mBulletSpeed;
}

void BulletClass::setSpeed(int speed) {
    this->mBulletSpeed = speed;
}

void BulletClass::init() {
    this->mBulletSpeed = B_SPEED;
    this->setSize(B_SIZE);
    this->setPosY(-this->getSize());
    this->setPosX(-this->getSize());
}