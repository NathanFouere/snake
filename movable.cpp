#include <stdio.h>
#include <constants.h>
#include <entity.hpp>
#include <movable.hpp>

Movable::Movable(int x, int y, bool waitingForMovement, bool queue): Entity(x, y) {
    this->direction = Direction::Right;
    this->waitingForMovement = waitingForMovement;
    this->queue = queue;
}

Direction Movable::getDirection() { return direction; }

void Movable::mooveFromMovable(Movable* Movable) {
    bool leftOf = this->leftOfOther(Movable);
    bool rightOf = this->rightOfOther(Movable);
    bool bottomOf = this->bottomfOther(Movable);
    bool topOf = this->topOfOther(Movable);

    Direction otherMovableDirection = Movable->getDirection();
    switch (otherMovableDirection) {
        case Direction::Down:
            if (leftOf) {
                this->setDirection(Direction::Right);
                break;
            }
            if (rightOf) {
                this->setDirection(Direction::Left);
                break;
            }
            this->setDirection(Direction::Down);
            break;
        case Direction::Left:
            if (bottomOf) {
                this->setDirection(Direction::Up);
                break;
            }
            if (topOf) {
                this->setDirection(Direction::Down);
                break;
            }
            this->setDirection(Direction::Left);
            break;
        case Direction::Right:
            if (bottomOf) {
                this->setDirection(Direction::Up);
                break;
            }
            if (topOf) {
                this->setDirection(Direction::Down);
                break;
            }
            this->setDirection(Direction::Right);
            break;
        case Direction::Up:
            if (leftOf) {
                this->setDirection(Direction::Right);
                break;
            }
            if (rightOf) {
                this->setDirection(Direction::Left);
                break;
            }
            this->setDirection(Direction::Up);
            break;
    }
}

bool Movable::isMovementAllowed(Direction direction) {
    switch (direction) {
        case Direction::Down:
            return this->direction != Direction::Up;
        case Direction::Up:
            return this->direction != Direction::Down;
        case Direction::Left:
            return this->direction != Direction::Right;
        case Direction::Right:
            return this->direction != Direction::Left;
        default:
            printf("Error to handle \n");
            return false;
    }
}

bool Movable::isWaitingForMovement() {
    return this->waitingForMovement;
}

void Movable::unsetIsWaitingForMovement() {
    this->waitingForMovement = false;
}

bool Movable::isQueue() {
    return this->queue;
}

void Movable::setIsQueue() {
    this->queue = true;
}

void Movable::unsetIsQueue() {
    this->queue = false;
}

bool Movable::leftOfOther(Movable* Movable) {
    return this->getX() < Movable->getX();
}

bool Movable::rightOfOther(Movable* Movable) {
    return this->getX() > Movable->getX();
}

bool Movable::bottomfOther(Movable* Movable) {
    return this->getY() > Movable->getY();
}

bool Movable::topOfOther(Movable* Movable) {
    return this->getY() < Movable->getY();
}

void Movable::setDirection(Direction direction) {
    this->direction = direction;
}

void Movable::mooveFromDirection() {
    switch (this->direction) {
        case Direction::Left:
            x--;
            break;
        case Direction::Right:
            x++;
            break;
        case Direction::Down:
            y++;
            break;
        case Direction::Up:
            y--;
            break;
    }
}

bool Movable::hasCollisionWithWall() {
    return this->getX() < 0 ||
        this->getX() > SCREEN_WIDTH ||
        this->getY() < 0 ||
        this->getY() + HEIGHT_ENTITY > SCREEN_HEIGHT;
}
