#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class EntityClass {
public:
    int getSize() {
        return this->mEntitySize;
    }

    int getPosX() {
        return this->mEntityX;
    }

    int getPosY() {
        return this->mEntityY;
    }


    void setSize(int size) {
        this->mEntitySize = size;
    }

    void setPosX(int x) {
        this->mEntityX = x;
    }

    void setPosY(int y) {
        this->mEntityY = y;
    }


private:
    int mEntitySize;
    int mEntityY;
    int mEntityX;
};

#endif