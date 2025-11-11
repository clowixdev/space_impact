#include <iostream>
#include <fstream>

#include "classes/boss.h"
#include "constants.h"

int BossClass::getLives() {
    return this->mBossLives;
}

void BossClass::setLives(int lives) {
    this->mBossLives = lives;
}

bool BossClass::hasReachedTop() {
    return this->mReachedTop;
}

bool BossClass::hasReachedBot() {
    return this->mReachedBot;
}


void BossClass::setReachedTop(bool reached) {
    this->mReachedTop = reached;
}

void BossClass::setReachedBot(bool reached) {
    this->mReachedBot = reached;
}


void BossClass::init() {
    this->setSize(70);
    this->setPosX(WINDOW_WIDTH - this->getSize() * 2);
    this->setPosY(WINDOW_HEIGHT / 2);
    this->mBossLives = 10;
    this->mReachedBot = false;
    this->mReachedTop = true;
}

void BossClass::changeLives(int life) {
    this->mBossLives += life;
}