#include <constants.h>
#include <unistd.h>
#include <cstddef>
#include <cstdio>
#include <Direction.hpp>
#include <entity.hpp>
#include <movable.hpp>

Movable::Movable(int x, int y) {
    entities.emplace_back(std::make_unique<Entity>(x, y, false, true));
    inCollision = false;
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
    Entity* queue = this->getQueue();
    for (auto& e : entities) {
        if (!e->isWaitingForMovement()) {
            e->mooveFromDirection();
        } else {
            if (!e->checkCollision(queue)) {
                e->unsetIsWaitingForMovement();
                e->setIsQueue();
            }
        }
    }
}

Entity* Movable::getQueue() {
    for (size_t i = this->entities.size() - 1; i >= 0; i--) {
        Entity* cur = this->entities.at(i).get();
        if (cur->isQueue()) {
            return cur;
        }
    }
    printf("ça va pas \n");
    return nullptr;  // todo gerer expt
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

    for (size_t i = 2; i < this->entities.size(); i++) {
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
    entities.emplace_back(std::make_unique<Entity>(x, y, true, false));
}
