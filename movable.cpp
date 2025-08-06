#include "movable.hpp"
#include "constants.h"
#include <stdio.h>


Movable::Movable(int x, int y, int w, int h) : Entity(x, y, w, h) {
}

void Movable::moveLeft()  { x--; }
void Movable::moveRight() { x++; }
void Movable::moveDown()  { y++; }
void Movable::moveUp()    { y--; }

bool Movable::hasCollisionWithWall() { 
    return this->getX() < 0 ||
        this->getX() > SCREEN_WIDTH || 
        this->getY() < 0 ||
        this->getY() + this->getH() > SCREEN_HEIGHT;
}