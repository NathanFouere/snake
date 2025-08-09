#pragma once
#include "entity.hpp"
#include <memory>
#include <vector>

class Movable {
    public:           
        Movable(int x, int y);
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
        void render();
        bool hasCollisionWithWall();           
        void render(SDL_Renderer* renderer);
        void hasCollisionWithEntity(Entity* entity);
    private:
        void gainSize();
        std::vector<std::unique_ptr<Entity>> entities;
        bool inCollision;
        void applyMovementsFromLead(Entity* lead);
};
