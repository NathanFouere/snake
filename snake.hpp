#pragma once
#include "Direction.hpp"
#include "entity.hpp"
#include "movable.hpp"
#include <memory>
#include <vector>

class Snake {
    public:           
        Snake(int x, int y);
         bool hasCollisionWithWall() const;           
         void render(SDL_Renderer* renderer) const;
         bool hasCollisionWithEntity(const Entity* entity);
        bool hasCollisionWithItself();
         void mooveToDirection(Direction direction) const;
        void update();
        void gainSize();
        int getSize();
        const std::vector<std::unique_ptr<Movable>>& getEntities() const;
    private:
        std::vector<std::unique_ptr<Movable>> entities;
        bool inCollision = false;
        void applyMovementsFromLead(Movable* lead) const;
        Movable* getLead();
        Movable* getQueue();
        int nbWaiting = 0;
};
