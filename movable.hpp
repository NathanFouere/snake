#pragma once
#include "Direction.hpp"
#include "entity.hpp"
#include <memory>
#include <vector>

class Movable {
    public:           
        Movable(int x, int y);
        void render();
        bool hasCollisionWithWall();           
        void render(SDL_Renderer* renderer);
        bool hasCollisionWithEntity(Entity* entity);
        bool hasCollisionWithItself();
        void mooveToDirection(Direction direction);
        void update();
        void gainSize();
    private:
        std::vector<std::unique_ptr<Entity>> entities;
        bool inCollision;
        void applyMovementsFromLead(Entity* lead);
        Entity* getLead();
};
