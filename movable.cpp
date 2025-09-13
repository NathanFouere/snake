#include <constants.h>
#include <cstdio>
#include <cstdlib>
#include <entity.hpp>
#include <movable.hpp>
#include <Direction.hpp>

using enum Direction;
Movable::Movable(int x, int y, bool waitingForMovement, bool queue):
    Entity(x, y),
    waitingForMovement(waitingForMovement),
    queue(queue)
{}

 Direction Movable::getDirection() const { return direction; }

void Movable::mooveFromMovable(const Movable* movable) {
    bool leftOf = this->leftOfOther(movable);
    bool rightOf = this->rightOfOther(movable);
    bool bottomOf = this->bottomfOther(movable);
    bool topOf = this->topOfOther(movable);

    Direction otherMovableDirection = movable->getDirection();
    switch (otherMovableDirection) {
        case Down:
            if (leftOf) {
                this->setDirection(Right);
                break;
            }
            if (rightOf) {
                this->setDirection(Left);
                break;
            }
            this->setDirection(Down);
            break;
        case Left:
            if (bottomOf) {
                this->setDirection(Up);
                break;
            }
            if (topOf) {
                this->setDirection(Down);
                break;
            }
            this->setDirection(Left);
            break;
        case Right:
            if (bottomOf) {
                this->setDirection(Up);
                break;
            }
            if (topOf) {
                this->setDirection(Down);
                break;
            }
            this->setDirection(Right);
            break;
        case Up:
            if (leftOf) {
                this->setDirection(Right);
                break;
            }
            if (rightOf) {
                this->setDirection(Left);
                break;
            }
            this->setDirection(Up);
            break;
    }
}

 bool Movable::isMovementAllowed([[maybe_unused]] Direction movementDirection) const {
    switch (direction) {
        using enum Direction;
        case Down:
            return this->direction != Up;
        case Up:
            return this->direction != Down;
        case Left:
            return this->direction != Right;
        case Right:
            return this->direction != Left;
        default:
            return false;
    }
}

bool Movable::isWaitingForMovement() const {
    return this->waitingForMovement;
}

void Movable::unsetIsWaitingForMovement() {
    this->waitingForMovement = false;
}

bool Movable::isQueue() const {
    return this->queue;
}

void Movable::setIsQueue() {
    this->queue = true;
}

void Movable::unsetIsQueue() {
    this->queue = false;
}

 bool Movable::leftOfOther(const Movable* Movable) const {
    return this->getX() < Movable->getX();
}

 bool Movable::rightOfOther(const Movable* Movable) const {
    return this->getX() > Movable->getX();
}

 bool Movable::bottomfOther(const Movable* Movable) const {
    return this->getY() > Movable->getY();
}

 bool Movable::topOfOther(const Movable* Movable) const {
    return this->getY() < Movable->getY();
}

 void Movable::setDirection(Direction newDirection) {
    this->direction = newDirection;
}

void Movable::mooveFromDirection() {
    switch (this->direction) {
        case Left:
            this->decreaseX();
            break;
        case Right:
            this->increaseX();
            break;
        case Down:
            this->increaseY();
            break;
        case Up:
            this->decreaseY();
            break;
    }
}

bool Movable::hasCollisionWithWall() {
    return this->getX() < 0 ||
        this->getX() + WIDTH_ENTITY > SCREEN_WIDTH ||
        this->getY() < 0 ||
        this->getY() + HEIGHT_ENTITY > SCREEN_HEIGHT;
}
