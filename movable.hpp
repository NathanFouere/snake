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
        void mooveToDirection(Direction direction);
        void update();
    private:
        void gainSize();
        std::vector<std::unique_ptr<Entity>> entities;
        bool inCollision;
        void applyMovementsFromLead(Entity* lead);
};
