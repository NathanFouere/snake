#pragma once
#include <entity.hpp>
#include <Direction.hpp>

class Movable : public Entity {
    public:
        Movable(int x, int y, bool waitingForMovement = false, bool queue = false);
        bool hasCollisionWithWall();    
        const Direction getDirection();
        void mooveFromMovable(Movable* entity);
        const bool leftOfOther(Movable* entity) const;
        const bool rightOfOther(Movable* entity) const;
        const bool bottomfOther(Movable* entity) const;
        const bool topOfOther(Movable* entity) const;
        const bool isMovementAllowed(Direction movementDirection) const;
        void mooveFromDirection();
        const void setDirection(Direction newDirection);
        bool isWaitingForMovement() const;
        void unsetIsWaitingForMovement();
        bool isQueue() const;
        void unsetIsQueue();
        void setIsQueue();
    private:
        Direction direction = Direction::Right;
        bool waitingForMovement;
        bool queue;
};