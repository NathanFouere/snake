#include "Direction.hpp"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <constants.h>
#include <cstdio>
#include <entity.hpp>

Entity::Entity(int x, int y) {
    this->x = x;
    this->y = y;
    this->direction = Direction::Right;
}

int Entity::getX() { return x; }
int Entity::getY() { return y; }
Direction Entity::getDirection() { return direction; }

SDL_Rect Entity::getRect() {
    return { this->getX(), this->getY(), WIDTH_ENTITY, HEIGHT_ENTITY};
}

void Entity::render(SDL_Renderer* renderer) {
    SDL_Rect rect = this->getRect();
    SDL_RenderFillRect(renderer, &rect);
}

void Entity::mooveFromEntity(Entity* entity) {
    bool leftOf = this->leftOfOther(entity);
    bool rightOf = this->rightOfOther(entity);
    bool bottomOf = this->bottomfOther(entity);
    bool topOf = this->topOfOther(entity);
    printf("leftof: %d, rightof: %d, bottomOf: %d, topOf: %d \n", leftOf, rightOf, bottomOf, topOf);
    
    Direction otherEntityDirection = entity->getDirection();
    switch (otherEntityDirection) {
        case Direction::Down:
            if (leftOf) {
                this->setDirection(Direction::Right);
                break;
            }
            if(rightOf) {
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
            if(topOf) {
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
            if(topOf) {
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
            if(rightOf) {
                this->setDirection(Direction::Left);
                break;
            }
            this->setDirection(Direction::Up);
            break;
    }
}

bool Entity::isMovementAllowed(Direction direction) {
    
    switch (direction) {
        case Direction::Down:
            printf("Asked diretion down and %d \n", this->direction != Direction::Up);
            return this->direction != Direction::Up;
        case Direction::Up:
        printf("Asked diretion Up and %d \n", this->direction != Direction::Down);
            return this->direction != Direction::Down;
        case Direction::Left:
        printf("Asked diretion Left and %d \n", this->direction != Direction::Right);
            return this->direction != Direction::Right;
        case Direction::Right:
        printf("Asked diretion Right and %d \n", this->direction != Direction::Left);
            return this->direction != Direction::Left;
        default:
            printf("Error to handle \n"); // todo
            return false;
    }
}

bool Entity::leftOfOther(Entity* entity) {
    return this->getX() < entity->getX();
}

bool Entity::rightOfOther(Entity* entity) {
    return this->getX() > entity->getX();
}

bool Entity::bottomfOther(Entity* entity) {
    return this->getY() > entity->getY();
}

bool Entity::topOfOther(Entity* entity) {
    return this->getY() < entity->getY();
}

void Entity::setDirection(Direction direction)  { 
    this->direction = direction;
}

void Entity::mooveFromDirection() {
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

bool Entity::hasCollisionWithWall() {
    return this->getX() < 0 ||
        this->getX() > SCREEN_WIDTH ||
        this->getY() < 0 ||
        this->getY() + HEIGHT_ENTITY > SCREEN_HEIGHT;
}

bool Entity::checkCollision(Entity* entity) {
    SDL_Rect rect = this->getRect();
    SDL_Rect rect2 = entity->getRect();
    
    return SDL_HasIntersection(&rect, &rect2);
}

