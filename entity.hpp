#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <Direction.hpp>

class Entity {
    public:
        int getX() const;
        int getY() const;
        Entity(int x, int y);
        SDL_Rect getRect();
        void render(SDL_Renderer* renderer);
        bool checkCollision(Entity* entity);
        bool checkCollisionWithPoint(int xPos, int yPos);
        ~Entity();
    protected:
        void setX(int xPos);
        void setY(int yPos);
        void increaseX();
        void increaseY();
        void decreaseX();
        void decreaseY();
    private:
        int x;
        int y;
};