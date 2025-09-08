#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <constants.h>
#include <cstdlib>
#include <entity.hpp>
#include <movable.hpp>
#include <fruit.hpp>

class Game {
    public: 
        Game();
        void gameLoop();
    private:
        SDL_Window* gWindow;
        Movable* snake;
        std::unique_ptr<Fruit>   fruit;
        SDL_Renderer* renderer;
        double dt;
        bool init();
        void render();
        void update();
        void close();
};