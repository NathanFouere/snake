#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <Direction.hpp>

class Entity {
    public:
        int getX();
        int getY();
        Entity(int x, int y);
        SDL_Rect getRect();
        void render(SDL_Renderer* renderer);
        bool checkCollision(Entity* entity);
        bool checkCollisionWithPoint(int xPos, int yPos);
        ~Entity();
    protected:
        int x;
        int y;
};