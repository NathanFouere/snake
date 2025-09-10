#pragma once
#include "SDL_pixels.h"
#include "snake.hpp"
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
        std::unique_ptr<Snake> snake;
        std::unique_ptr<Fruit>   fruit;
        SDL_Renderer* renderer;
        double dt;
        TTF_Font* font;
        bool gameOver;
        SDL_Rect scoreTestRect;
        SDL_Rect gameOverTestRect;

        bool init();
        void render();
        void update();
        void close();
        void setGameIsOver();
        void displayText(std::string text, SDL_Rect textDst, SDL_Color color = {255, 255, 255});
};