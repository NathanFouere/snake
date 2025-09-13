#pragma once
#include <entity.hpp>
#include <Direction.hpp>

class Movable : public Entity {
    public:
        Movable(int x, int y, bool waitingForMovement = false, bool queue = false);
        bool hasCollisionWithWall() const;    
         Direction getDirection() const;
        void mooveFromMovable(const Movable* entity);
         bool leftOfOther(const Movable* entity) const;
         bool rightOfOther(const Movable* entity) const;
         bool bottomfOther(const Movable* entity) const;
         bool topOfOther(const Movable* entity) const;
         bool isMovementAllowed([[maybe_unused]] Direction movementDirection) const;
        void mooveFromDirection();
        void setDirection(Direction newDirection);
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