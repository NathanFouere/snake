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
    SDL_Rect rect = this->getRect();
    SDL_Rect rect2 = entity->getRect();

    return SDL_HasIntersection(&rect, &rect2);
}
