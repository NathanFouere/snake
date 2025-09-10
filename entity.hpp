#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <Direction.hpp>

class Entity {
    public:
        int getX();
        int getY();
        Entity(int x, int y, bool waitingForMovement = false, bool queue = false); // TODO, ajouter constructeur create from other entity
        SDL_Rect getRect();
        void render(SDL_Renderer* renderer);
        bool hasCollisionWithWall();    
        bool checkCollision(Entity* entity);
        Direction getDirection();
        void mooveFromEntity(Entity* entity);
        bool leftOfOther(Entity* entity);
        bool rightOfOther(Entity* entity);
        bool bottomfOther(Entity* entity);
        bool topOfOther(Entity* entity);
        bool isMovementAllowed(Direction direction);
        void mooveFromDirection();
        void setDirection(Direction direction);
        bool isWaitingForMovement();
        void unsetIsWaitingForMovement();
        bool isQueue();
        void unsetIsQueue();
        void setIsQueue();
        ~Entity();
    private:
        int x;
        int y;
        Direction direction;
        bool waitingForMovement;
        bool queue;
};