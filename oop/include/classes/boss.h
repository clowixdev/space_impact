#ifndef BOSS_H
#define BOSS_H

#include <iostream>

#include "entity.h"

using namespace std;

class BossClass : public EntityClass {
public:
    BossClass(int bossLives = -1, int bossSize = -1, int bossX = -1, int bossY = -1, bool reachedTop = false, bool reachedBot = false) : 
        mBossLives(bossLives),
        mReachedBot(reachedBot),
        mReachedTop(reachedTop)
    { 
        this->setSize(bossSize);
        this->setPosX(bossX);
        this->setPosY(bossY);
    }

    int getLives();
    bool hasReachedTop();
    bool hasReachedBot();

    void setLives(int lives);
    void setReachedTop(bool reached);
    void setReachedBot(bool reached);

    void init();
    void changeLives(int life);

private:
    int mBossLives;
    bool mReachedTop;
    bool mReachedBot;
};

#endif