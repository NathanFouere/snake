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

const Direction Movable::getDirection() { return direction; }

void Movable::mooveFromMovable(Movable* Movable) {
    bool leftOf = this->leftOfOther(Movable);
    bool rightOf = this->rightOfOther(Movable);
    bool bottomOf = this->bottomfOther(Movable);
    bool topOf = this->topOfOther(Movable);

    Direction otherMovableDirection = Movable->getDirection();
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

bool Movable::isMovementAllowed(Direction movementDirection) {
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
            std::printf("Error to handle \n");
            return false;
    }
}

const bool Movable::isWaitingForMovement() {
    return this->waitingForMovement;
}

void Movable::unsetIsWaitingForMovement() {
    this->waitingForMovement = false;
}

const bool Movable::isQueue() {
    return this->queue;
}

void Movable::setIsQueue() {
    this->queue = true;
}

void Movable::unsetIsQueue() {
    this->queue = false;
}

const bool Movable::leftOfOther(Movable* Movable) {
    return this->getX() < Movable->getX();
}

const bool Movable::rightOfOther(Movable* Movable) {
    return this->getX() > Movable->getX();
}

const bool Movable::bottomfOther(Movable* Movable) {
    return this->getY() > Movable->getY();
}

const bool Movable::topOfOther(Movable* Movable) {
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
