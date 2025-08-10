#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <Direction.hpp>

class Entity {
    public:
        int getX();
        int getY();
        Entity(int x, int y); // TODO, ajouter constructeur create from other entity
        SDL_Rect getRect();
        void render(SDL_Renderer* renderer);
        bool hasCollisionWithWall();           
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
        bool checkCollision(Entity* entity);
        Direction getDirection();
        void mooveFromEntity(Entity* entity);
        bool leftOfOther(Entity* entity);
        bool rightOfOther(Entity* entity);
        bool bottomfOther(Entity* entity);
        bool topOfOther(Entity* entity);
        bool isMovementAllowed(Direction direction);
    private:
        int x;
        int y;
        Direction direction;
};