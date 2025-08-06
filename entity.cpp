#include "entity.hpp"

Entity::Entity(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

int Entity::getX() { return x; }
int Entity::getY() { return y; }
int Entity::getW() { return w; }
int Entity::getH() { return h; }