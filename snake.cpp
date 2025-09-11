#include <constants.h>
#include <unistd.h>
#include <cstddef>
#include <cstdio>
#include <movable.hpp>
#include <Direction.hpp>
#include <entity.hpp>
#include <snake.hpp>

Snake::Snake(int x, int y) {
    this->entities.emplace_back(std::make_unique<Movable>(x, y, false, true));
    this->inCollision = false;
    this->nbWaiting = 0;
}


void Snake::render(SDL_Renderer* renderer) {
    for (auto& e : entities) {
        e->render(renderer);
    }
}

void Snake::applyMovementsFromLead(Movable* lead) {
    for (std::size_t i = 1; i < entities.size(); ++i) {
        Movable* cur = entities.at(i).get();
        cur->mooveFromMovable(lead);
        lead = cur;
    }
}

int Snake::getSize() {
    return this->entities.size();
}

void Snake::update() {
    Movable* lead = entities.front().get();
    this->applyMovementsFromLead(lead);
    Movable* queue = this->getQueue();
    for (auto& e : entities) {
        if (!e->isWaitingForMovement()) {
            e->mooveFromDirection();
        } else {
            if (!e->checkCollision(queue)) {
                this->nbWaiting--;
                e->unsetIsWaitingForMovement();
                e->setIsQueue();
            }
        }
    }
}

Movable* Snake::getQueue() {
    for (size_t i = this->entities.size() - 1; i >= 0; i--) {
        Movable* cur = this->entities.at(i).get();
        if (cur->isQueue()) {
            return cur;
        }
    }
    printf("ça va pas \n");
    return nullptr;  // todo gerer expt
}

void Snake::mooveToDirection(Direction direction) {
    Movable* lead = entities.front().get();
    if (!lead->isMovementAllowed(direction)) {
        return;
    }
    Movable* behind = (entities.size() >= 1) ? entities[1].get() : nullptr;
    if (behind != nullptr && !behind->isMovementAllowed(direction)) {
        return;
    }
    lead->setDirection(direction);
}

bool Snake::hasCollisionWithWall() {
    for (auto& e : entities) {
        if (e->hasCollisionWithWall()) {
            return true;
        }
    }

    return false;
}

bool Snake::hasCollisionWithEntity(Entity* entity) {
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

const std::vector<std::unique_ptr<Movable>>& Snake::getEntities() const {
    return this->entities;
}

bool Snake::hasCollisionWithItself() {
    Entity* lead = this->getLead();

    for (size_t i = this->nbWaiting + 2; i < this->entities.size(); i++) {
        if (lead->checkCollision(this->entities.at(i).get())) {
            return true;
        }
    }

    return false;
}

Movable* Snake::getLead() {
    return entities.front().get();
}


void Snake::gainSize() {
    Entity* lastEl = this->entities.back().get();
    int x = lastEl->getX();
    int y = lastEl->getY();
    entities.emplace_back(std::make_unique<Movable>(x, y, true, false));
    this->nbWaiting++;
}
