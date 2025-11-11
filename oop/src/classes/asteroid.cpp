#include <iostream>
#include <fstream>

#include "classes/asteroid.h"
#include "constants.h"

int AsteroidClass::getSpeed() {
    return this->mAsteroidSpeed;
}

void AsteroidClass::setSpeed(int speed) {
    this->mAsteroidSpeed = speed;
}

void AsteroidClass::init(int size, int speed) {
    this->mAsteroidSpeed = speed;
    this->setSize(size);
    this->setPosY(-this->getSize());
    this->setPosX(WINDOW_WIDTH - this->getSize());
}