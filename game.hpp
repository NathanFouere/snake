#pragma once
#include <SDL2/SDL.h>
#include <constants.h>
#include <cstdlib>
#include <entity.hpp>
#include <movable.hpp>
#include <fruit.hpp>
#include <SDL_ttf.h>

class Game {
    public: 
        Game();
        void gameLoop();
    private:
        SDL_Window* gWindow;
        std::unique_ptr<Movable> snake;
        std::unique_ptr<Fruit>   fruit;
        SDL_Renderer* renderer;
        double dt;
        TTF_Font* font;

        bool init();
        void render();
        void update();
        void close();
};