#include <constants.h>
#include <cstddef>
#include <cstdio>
#include <Direction.hpp>
#include <entity.hpp>
#include <movable.hpp>
#include <unistd.h>


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

void Movable::update() {
    Entity* lead = entities.front().get();
    this->applyMovementsFromLead(lead);
    for (auto& e : entities) {
        e->mooveFromDirection();
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
    lead->setDirection(direction);
}

bool Movable::hasCollisionWithWall() {
    for (auto& e : entities) {
        if (e->hasCollisionWithWall()) {
            return true;
        }
    }

    return false;
}

bool Movable::hasCollisionWithEntity(Entity* entity) {
    bool hadCollision = false;
    for (auto& e : entities) {
        if ( e->checkCollision(entity) ) {
            hadCollision = true;
            break;
        }
    }
    if ( hadCollision && !this->inCollision ) {
        this->inCollision = true;
        return true;
    }
    if ( !hadCollision ) {
        this->inCollision = false;
    }
    return false;
}

bool Movable::hasCollisionWithItself() {
    Entity* lead = this->getLead();
    
    for(size_t i = 2; i < this->entities.size(); i++) {
        if (lead->checkCollision(this->entities.at(i).get())) {
            return true;
        }
    }
    
    return false;
}

Entity* Movable::getLead() {
    return entities.front().get();
}


void Movable::gainSize() {
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

