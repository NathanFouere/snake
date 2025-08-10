#include "Direction.hpp"
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

SDL_Window* gWindow = NULL;
SDL_Renderer* renderer;
Movable* snake = new Movable(100, 100);
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    snake->render(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    fruit->render(renderer);
}

void update() {
    snake->hasCollisionWithEntity(fruit);
    snake->update();
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
            update();

            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            snake->mooveToDirection(Direction::Up);
                            break;
                        case SDLK_DOWN:
                            snake->mooveToDirection(Direction::Down);
                            break;
                        case SDLK_LEFT:
                            snake->mooveToDirection(Direction::Left);
                            break;
                        case SDLK_RIGHT:
                            snake->mooveToDirection(Direction::Right);
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
