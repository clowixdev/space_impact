#include <iostream>
#include <fstream>

#include "classes/heart.h"
#include "constants.h"

int HeartClass::getSpeed() {
    return this->mHeartSpeed;
}

bool HeartClass::isSpawning() {
    return this->mIsSpawning;
}

void HeartClass::setSpeed(int speed) {
    this->mHeartSpeed = speed;
}

void HeartClass::setSpawning(bool spawn) {
    this->mIsSpawning = spawn;
}

void HeartClass::init() {
    this->setSize(30);
    this->setPosX(WINDOW_WIDTH - this->getSize());
    this->setPosY(-this->getSize());
    this->mIsSpawning = true;
    this->mHeartSpeed = 4;
}