#pragma once
#include <entity.hpp>
#include <Direction.hpp>

class Movable : public Entity {
    public:
        Movable(int x, int y, bool waitingForMovement = false, bool queue = false);
        bool hasCollisionWithWall();    
        Direction getDirection();
        void mooveFromMovable(Movable* entity);
        bool leftOfOther(Movable* entity);
        bool rightOfOther(Movable* entity);
        bool bottomfOther(Movable* entity);
        bool topOfOther(Movable* entity);
        bool isMovementAllowed(Direction direction);
        void mooveFromDirection();
        void setDirection(Direction direction);
        bool isWaitingForMovement();
        void unsetIsWaitingForMovement();
        bool isQueue();
        void unsetIsQueue();
        void setIsQueue();
    private:
        Direction direction = Direction::Right;
        bool waitingForMovement;
        bool queue;
};