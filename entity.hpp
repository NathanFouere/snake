#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <Direction.hpp>

class Entity {
    public:
        const int getX();
        const int getY();
        Entity(int x, int y);
        SDL_Rect getRect();
        void render(SDL_Renderer* renderer);
        bool checkCollision(Entity* entity);
        bool checkCollisionWithPoint(int xPos, int yPos);
        ~Entity();
    protected:
        const void setX(int xPos);
        const void setY(int yPos);
        const void increaseX();
        const void increaseY();
        const void decreaseX();
        const void decreaseY();
    private:
        int x;
        int y;
};