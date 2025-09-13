#pragma once
#include <entity.hpp>
#include <Direction.hpp>

class Movable : public Entity {
    public:
        Movable(int x, int y, bool waitingForMovement = false, bool queue = false);
        bool hasCollisionWithWall();    
        const Direction getDirection();
        void mooveFromMovable(Movable* entity);
        const bool leftOfOther(Movable* entity);
        const bool rightOfOther(Movable* entity);
        const bool bottomfOther(Movable* entity);
        const bool topOfOther(Movable* entity);
        bool isMovementAllowed(Direction movementDirection);
        void mooveFromDirection();
        void setDirection(Direction newDirection);
        const bool isWaitingForMovement();
        void unsetIsWaitingForMovement();
        const bool isQueue();
        void unsetIsQueue();
        void setIsQueue();
    private:
        Direction direction = Direction::Right;
        bool waitingForMovement;
        bool queue;
};