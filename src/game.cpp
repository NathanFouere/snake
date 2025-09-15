#include "SDL_keycode.h"
#include <constants.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <string>
#include <game.hpp>
#include <entity.hpp>
#include <movable.hpp>
#include <fruit.hpp>
#include <Direction.hpp>
#include <SDL_render.h>
#include <snake.hpp>


Game::Game() = default;

void Game::displayText(const std::string& text, SDL_Rect textDst, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(this->font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textDst);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    snake->render(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    fruit->render(renderer);
    this->displayScore();
    if (true == this->gameOver) {
        this->displayGameOver();
    }
}

void Game::displayScore() {
    this->displayText("Score: " + std::to_string(this->snake->getSize()), this->scoreTestRect);
}

void Game::displayGameOver() {
    this->displayText("Game Over !", this->gameOverTestRect, {255, 0, 0});
}

void Game::setGameIsOver() {
    this->gameOver = true;
}

void Game::update() {
    if (true == this->gameOver) {
        return;
    }

    if (true == snake->hasCollisionWithWall()) {
        this->setGameIsOver();
        return;
    }

    if (true == snake->hasCollisionWithItself()) {
        this->setGameIsOver();
        return;
    }

    if (true == snake->hasCollisionWithEntity(this->fruit.get())) {
        fruit.reset();
        snake->gainSize();
        this->fruit = std::make_unique<Fruit>(*this->snake);
    }

    snake->update();
}

int Game::gameLoop() {
    if (!init()) {
        return -1;
    } else {
        bool quit = false;
        SDL_Event e;
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 freq = SDL_GetPerformanceFrequency();
        double accumulator = 0.0;
        while (!quit) {
            Uint64 newTicks = SDL_GetPerformanceCounter();
            auto frameTime = (newTicks - now) / static_cast<double>(freq);
            now = newTicks;
            accumulator += frameTime;
            while (accumulator >= dt) {
                update();
                accumulator -= dt;
            }
            render();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    this->handleKeyboardInput(e);
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
    close();
    return 0;
}

void Game::handleKeyboardInput(const SDL_Event& e) const {
    switch (e.key.keysym.sym) {
        using enum Direction;
        case SDLK_UP:
            snake->mooveToDirection(Up);
            break;
        case SDLK_DOWN:
            snake->mooveToDirection(Down);
            break;
        case SDLK_LEFT:
            snake->mooveToDirection(Left);
            break;
        case SDLK_RIGHT:
            snake->mooveToDirection(Right);
            break;
        default:
            break;
    }
}

void Game::close() {
    TTF_CloseFont(font);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    SDL_Quit();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    } else {
        gWindow = SDL_CreateWindow(
            "Snake",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            std::printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        renderer = SDL_CreateRenderer(
            gWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }

    if ( TTF_Init() < 0 ) {
        std::printf("SDL could not initialize! SDL Error: %s\n", TTF_GetError());
        return false;
    }
    font = TTF_OpenFont("assets/Basic-Regular.ttf", 72);
    if ( !font ) {
        std::printf("SDL could not initialize! SDL Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}
