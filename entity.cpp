#include "SDL_rect.h"
#include "SDL_render.h"
#include <constants.h>
#include <cstdio>
#include <Direction.hpp>
#include <entity.hpp>

Entity::Entity(int x, int y) {
    this->x = x;
    this->y = y;
}

Entity::~Entity() = default;
int Entity::getX() { return x; }
int Entity::getY() { return y; }

SDL_Rect Entity::getRect() {
    return { this->getX(), this->getY(), WIDTH_ENTITY, HEIGHT_ENTITY};
}

void Entity::render(SDL_Renderer* renderer) {
    SDL_Rect rect = this->getRect();
    SDL_RenderFillRect(renderer, &rect);
}

bool Entity::checkCollision(Entity* entity) {
    bool condOne = this->getX() < entity->getX() + WIDTH_ENTITY;
    bool condTwo = this->getX() + WIDTH_ENTITY > entity->getX();
    bool condThree = this->getY() < entity->getY() + HEIGHT_ENTITY;
    bool condFour = this->getY() + HEIGHT_ENTITY > entity->getY();
    bool collisionDetected = condOne && condTwo && condThree && condFour;

    return collisionDetected;
}

bool Entity::checkCollisionWithPoint(int x, int y) {
    bool condOne = this->getX() < x + WIDTH_ENTITY;
    bool condTwo = this->getX() + WIDTH_ENTITY > x;
    bool condThree = this->getY() < y + HEIGHT_ENTITY;
    bool condFour = this->getY() + HEIGHT_ENTITY > y;
    bool collisionDetected = condOne && condTwo && condThree && condFour;

    return collisionDetected;
}
