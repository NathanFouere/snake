#pragma once
#include "SDL_pixels.h"
#include <SDL2/SDL.h>
#include <constants.h>
#include <cstdlib>
#include <entity.hpp>
#include <movable.hpp>
#include <fruit.hpp>
#include <snake.hpp>
#include <SDL_ttf.h>

class Game {
    public: 
        Game();
        int gameLoop();
    private:
        SDL_Window* gWindow = nullptr;
        std::unique_ptr<Snake> snake = std::make_unique<Snake>(100, 100);
        std::unique_ptr<Fruit>   fruit = std::make_unique<Fruit>();
        SDL_Renderer* renderer= nullptr;
        double dt= 1 / 200.0;
        TTF_Font* font = nullptr;
        bool gameOver = false;
        SDL_Rect scoreTestRect = {SCREEN_WIDTH - 130, 0, 125, 50};
        SDL_Rect gameOverTestRect = {(SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 50, 255, 50};

        bool init();
        void render();
        void update();
        void close();
        void setGameIsOver();
        void displayText(const std::string& text, SDL_Rect textDst, SDL_Color color = {255, 255, 255});
        void handleKeyboardInput(const SDL_Event& e) const;
        void displayScore();
        void displayGameOver();
};