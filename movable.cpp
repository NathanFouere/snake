#include "movable.hpp"

Movable::Movable(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

int Movable::getX() { return x; }
int Movable::getY() { return y; }
int Movable::getW() { return w; }
int Movable::getH() { return h; }


void Movable::moveLeft()  { x--; }
void Movable::moveRight() { x++; }
void Movable::moveDown()  { y++; }
void Movable::moveUp()    { y--; }