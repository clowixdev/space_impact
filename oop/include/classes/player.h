#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "entity.h"

using namespace std;

class PlayerClass : public EntityClass {
public:
    PlayerClass(int currentLevel = -1, int playerSize = -1, int playerX = -1, int playerY = -1, int playerScore = -1, int playerLives = -1, bool godMode = false) : 
        mCurrentLevel(currentLevel),
        mPlayerScore(playerScore),
        mPlayerLives(playerLives),
        mGodMode(godMode)
    { 
        this->setSize(playerSize);
        this->setPosX(playerX);
        this->setPosY(playerY);
    }

    int getLevel();
    int getScore();
    int getLives();
    int inGodMode();

    void setLevel(int level);
    void setScore(int score);
    void setLives(int lives);
    void setGodMod(bool mode);

    void init();

private:
    int mCurrentLevel;
    int mPlayerScore;
    int mPlayerLives;
    bool mGodMode;
};

#endif