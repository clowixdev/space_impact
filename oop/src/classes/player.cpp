#include <iostream>

#include "classes/player.h"
#include "constants.h"
    
int PlayerClass::getLevel() {
    return this->mCurrentLevel;
}

int PlayerClass::getScore() {
    return this->mPlayerScore;
}

int PlayerClass::getLives() {
    return this->mPlayerLives;
}

int PlayerClass::inGodMode() {
    return this->mGodMode;
}


void PlayerClass::setLevel(int level) {
    this->mCurrentLevel = level;
}

void PlayerClass::setScore(int score) {
    this->mPlayerScore = score;
}

void PlayerClass::setLives(int lives) {
    this->mPlayerLives = lives;
}

void PlayerClass::setGodMod(bool mode) {
    this->mGodMode = mode;
}

void PlayerClass::init() {
    this->mCurrentLevel = 1;
    this->setSize(50);
    this->setPosX(this->getSize());
    this->setPosY(WINDOW_HEIGHT / 2);
    this->mPlayerScore = 0;
    this->mPlayerLives = 3;
    this->mGodMode = false;
}
