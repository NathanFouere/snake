#include <SDL2/SDL.h>
#include <stdio.h>
#include <constants.h>
#include <cstdlib>
#include <entity.hpp>
#include <movable.hpp>
#include <fruit.hpp>

bool init();

void close();

void render();

bool checkCollision(Entity* entityOne, Entity* entityTwo) {
    bool condOne = entityTwo->getX() < entityOne->getX() + entityOne->getW();
    bool condTwo = entityTwo->getX() + entityTwo->getW() > entityOne->getX();
    bool condThree = entityTwo->getY() < entityOne->getY() + entityOne->getH();
    bool condFour = entityTwo->getY() + entityTwo->getH() >entityOne->getY();

    bool collisionDetected = condOne && condTwo && condThree && condFour;
    if (collisionDetected) {
        printf("COLLISION !!! \n");
    }
    return collisionDetected;
}

SDL_Window* gWindow = NULL;
SDL_Renderer* renderer;
Movable* snake = new Movable(100, 100, 50, 50);
Fruit* fruit = new Fruit();

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow(
            "SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        renderer = SDL_CreateRenderer(
            gWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
    return success;
}

void render() {
    checkCollision(snake, fruit);
    bool outsideOfWalls = snake->hasCollisionWithWall();
    if (outsideOfWalls) {
        printf("dehors \n");
    } else {
        printf("pas dehors \n");
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect snakeRect = {
        snake->getX(), snake->getY(), snake->getW(), snake->getH()
    };
    SDL_RenderFillRect(renderer, &snakeRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect fruitRect = {
        fruit->getX(), fruit->getY(), fruit->getW(), fruit->getH()
    };
    SDL_RenderFillRect(renderer, &fruitRect);
}

void close() {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        bool quit = false;
        SDL_Event e;

        while (!quit) {
            render();

            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            snake->moveUp();
                            break;
                        case SDLK_DOWN:
                            snake->moveDown();
                            break;
                        case SDLK_LEFT:
                            snake->moveLeft();
                            break;
                        case SDLK_RIGHT:
                            snake->moveRight();
                            break;
                        default:
                            break;
                    }
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
    close();
    return 0;
}
