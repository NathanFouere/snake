#include <constants.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <cstddef>
#include <game.hpp>
#include <entity.hpp>
#include <movable.hpp>
#include <fruit.hpp>
#include <Direction.hpp>
#include <SDL_render.h>
#include <snake.hpp>
#include <string>


Game::Game()  {
    this->gWindow = nullptr;
    this->renderer = nullptr;
    this->font = nullptr;
    this->dt = 1 / 60.0;
    this->gameOver = false;
    this->snake = std::make_unique<Snake>(100, 100);
    this->fruit = std::make_unique<Fruit>();
    this->scoreTestRect = {SCREEN_WIDTH - 130, 0, 125, 50};
    this->gameOverTestRect = {(SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 50, 255, 50};
}

void Game::displayText(std::string text, SDL_Rect textDst, SDL_Color color) {
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
    this->displayText("Score: " + std::to_string(this->snake->getSize()), this->scoreTestRect);
}

void Game::setGameIsOver() {
    this->gameOver = true;
}

void Game::update() {
    if (true == this->gameOver) {
        this->displayText("Game Over !", {255, 0, 0});
    }

    bool collisionBetweenSnakeAndWall = snake->hasCollisionWithWall();
    if (true == collisionBetweenSnakeAndWall) {
        this->setGameIsOver();
        return;
    }

    bool hasCollisionWithItself = snake->hasCollisionWithItself();
    if (true == hasCollisionWithItself) {
        this->setGameIsOver();
        return;
    }

    bool snakeEatsFruit = snake->hasCollisionWithEntity(this->fruit.get());
    if (true == snakeEatsFruit) {
        fruit.reset();
        snake->gainSize();
        this->fruit = std::make_unique<Fruit>();
    }

    snake->update();
}

void Game::gameLoop() {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        bool quit = false;
        SDL_Event e;
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 freq = SDL_GetPerformanceFrequency();
        double accumulator = 0.0;
        while (!quit) {
            Uint64 newTicks = SDL_GetPerformanceCounter();
            double frameTime = static_cast<double>((newTicks - now) / static_cast<double>(freq));
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
}

void Game::close() {
    TTF_CloseFont(font);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}

bool Game::init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow(
            "Snake",
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

    if ( TTF_Init() < 0 ) {
        printf("SDL could not initialize! SDL Error: %s\n", TTF_GetError());
        success = false;
    }
    font = TTF_OpenFont("Basic-Regular.ttf", 72);
    if ( !font ) {
        printf("SDL could not initialize! SDL Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
}
