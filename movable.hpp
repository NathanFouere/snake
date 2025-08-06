#pragma once
#include "entity.hpp"

class Movable: public Entity {
    public:           
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
        Movable(int x, int y, int w, int h);
        bool hasCollisionWithWall();
};
