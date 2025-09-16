#include <constants.h>
#include <unistd.h>
#include <vector>
#include <cstddef>
#include <cstdio>
#include <movable.hpp>
#include <Direction.hpp>
#include <entity.hpp>
#include <snake.hpp>

Snake::Snake(int x, int y) {
    this->entities.emplace_back(std::make_unique<Movable>(x, y, false, true));
}


void Snake::render(SDL_Renderer* renderer) const {
    for (const auto& e : entities) {
        e->render(renderer);
    }
}

void Snake::applyMovementsFromLead(const Movable* lead) const {
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
    const Movable* queue = this->getQueue();
    for (auto& e : entities) {
        if (!e->isWaitingForMovement()) {
            e->mooveFromDirection();
        } else {
            if (queue->getDirection() != e->getDirection()) {
                e->mooveFromDirection();
            }
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
    return nullptr;  // todo gerer expt
}

void Snake::mooveToDirection(Direction direction) const {
    Movable* lead = entities.front().get();
    if (!lead->isMovementAllowed(direction)) {
        return;
    }
    const Movable* behind = (entities.size() >= 1) ? entities[1].get() : nullptr;
    if (behind != nullptr && !behind->isMovementAllowed(direction)) {
        return;
    }
    lead->setDirection(direction);
}

bool Snake::hasCollisionWithWall() const {
    for (const auto& e : entities) {
        if (e->hasCollisionWithWall()) {
            return true;
        }
    }

    return false;
}

bool Snake::hasCollisionWithEntity(const Entity* entity) {
    bool hadCollision = false;
    for (const auto& e : entities) {
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
    const Entity* lastEl = this->entities.back().get();
    entities.emplace_back(std::make_unique<Movable>(lastEl->getX(), lastEl->getY(), true, false));
    this->nbWaiting++;
}
