#include "Direction.hpp"
#include "SDL_rect.h"
#include "constants.h"
#include "entity.hpp"
#include <cstdio>
#include <movable.hpp>


Movable::Movable(int x, int y) {
    entities.emplace_back(std::make_unique<Entity>(x, y));
    inCollision = false;
    this->gainSize();
    this->gainSize();
}


void Movable::render(SDL_Renderer* renderer) {
    for (auto& e : entities) {
        e->render(renderer);
    }
}

void Movable::applyMovementsFromLead(Entity* lead) {
    for (std::size_t i = 1; i < entities.size(); ++i) {
        Entity* cur = entities.at(i).get();
        cur->mooveFromEntity(lead);
        lead = cur;
    }
}

void Movable::mooveToDirection(Direction direction) {
    Entity* lead = entities.front().get();
    if (!lead->isMovementAllowed(direction)) {
        return;
    }
    Entity* behind = (entities.size() >= 1) ? entities[1].get() : nullptr;
    if (behind != nullptr && !behind->isMovementAllowed(direction)) {
        printf("is isMovementAllowed : %d \n", behind->isMovementAllowed(direction));
        return;
    }
    switch (direction) {
        case Direction::Up:
            lead->moveUp();
            break;
        case Direction::Right:
            lead->moveRight();
            break;
        case Direction::Down:
            lead->moveDown();
            break;
        case Direction::Left:
            lead->moveLeft();
            break;
    }
    this->applyMovementsFromLead(lead);
}

bool Movable::hasCollisionWithWall() {
    for (auto& e : entities) {
        if(e->hasCollisionWithWall()) {
            return true;
        }
    }
    
    return false;
}

void Movable::hasCollisionWithEntity(Entity* entity) {
    bool hadCollision = false;
    for (auto& e : entities) {
        if(e->checkCollision(entity)) {
            hadCollision = true;
            break;
        }
    }
    if(hadCollision && !this->inCollision) {
        printf("grandi snake\n");
        this->inCollision = true;
        this->gainSize();
    }
    if(!hadCollision){
        this->inCollision = false;
    }
}

void Movable::gainSize() {
    // TODO => gérer cas ou vide
    Entity* lastEl = this->entities.back().get();
    int x = lastEl->getX();
    int y = lastEl->getY();
    Direction lastEntityDirection = lastEl->getDirection();
    switch (lastEntityDirection) {
        case Direction::Down:
            y -= HEIGHT_ENTITY;
            break;
        case Direction::Left:
            x += WIDTH_ENTITY;
            break;
        case Direction::Right:
            x -= WIDTH_ENTITY;
            break;
        case Direction::Up:
            y += HEIGHT_ENTITY;
            break;
    }
    entities.emplace_back(std::make_unique<Entity>(x, y));
}

