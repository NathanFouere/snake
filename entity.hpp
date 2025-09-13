#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <Direction.hpp>

class Entity {
    public:
        int getX() const;
        int getY() const;
        Entity(int x, int y);
         SDL_Rect getRect() const;
         void render(SDL_Renderer* renderer) const;
         bool checkCollision(const Entity* entity) const;
        bool checkCollisionWithPoint(int xPos, int yPos) const;
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