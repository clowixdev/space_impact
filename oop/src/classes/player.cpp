#include <iostream>
#include <fstream>

#include "classes/player.h"
#include "constants.h"

// fstream logfile("./logfile.txt", ios::app);

int PlayerClass::getLevel() {
    // logfile << "[L] Returned " << this->mCurrentLevel << endl;
    return this->mCurrentLevel;
}

int PlayerClass::getScore() {
    // logfile << "[PS] Returned " << this->mPlayerScore << endl;
    return this->mPlayerScore;
}

int PlayerClass::getLives() {
    // logfile << "[PL] Returned " << this->mPlayerLives << endl;
    return this->mPlayerLives;
}

int PlayerClass::inGodMode() {
    // logfile << "[GM] Returned " << this->mGodMode << endl;
    return this->mGodMode;
}


void PlayerClass::setLevel(int level) {
    this->mCurrentLevel = level;
    // logfile << "[L] Set " << level << ". Now: " << this->mCurrentLevel << endl;
}

void PlayerClass::setScore(int score) {
    this->mPlayerScore = score;
    // logfile << "[PS] Set " << score << ". Now: " << this->mPlayerScore << endl;
}

void PlayerClass::setLives(int lives) {
    this->mPlayerLives = lives;
    // logfile << "[PL] Set " << lives << ". Now: " << this->mPlayerLives << endl;
}

void PlayerClass::setGodMod(bool mode) {
    this->mGodMode = mode;
    // logfile << "[GM] Set " << mode << ". Now: " << this->mGodMode << endl;
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

void PlayerClass::changeLives(int life) {
    this->mPlayerLives += life;
    // logfile << "[PL] Changed " << life << ". Now: " << this->mPlayerLives << endl;
}


void PlayerClass::changeScore(int score) {
    this->mPlayerScore += score;
    // logfile << "[PS] Changed " << score << ". Now: " << this->mPlayerScore << endl;
}