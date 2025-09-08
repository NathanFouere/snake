#include <cstddef>
#include <game.hpp>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <constants.h>
#include <cstdlib>
#include <entity.hpp>
#include <movable.hpp>
#include <fruit.hpp>
#include <Direction.hpp>
#include <memory>
#include <SDL_render.h>

SDL_Surface* text;
SDL_Color color = { 255, 255, 255 };
SDL_Texture* text_texture;
SDL_Rect textDst{(SCREEN_WIDTH / 2) - 125,(SCREEN_HEIGHT / 2) - 50,255,50};

Game::Game()  {
    gWindow = NULL;
    snake = new Movable(100, 100);
    fruit = std::make_unique<Fruit>();
    color = { 255, 255, 255 };
    dt = 1 / 60.0;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    snake->render(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    fruit->render(renderer);
}

void Game::update() {
    bool hasCollision = snake->hasCollisionWithEntity(this->fruit.get());
    if (true == hasCollision) {
        fruit.reset();
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
            double frameTime = (double)(newTicks - now) / (double)freq;
            now = newTicks;
            accumulator += frameTime;
            while (accumulator >= dt) {
                update();
                accumulator -= dt;
            }
            render();
            SDL_RenderCopy(renderer, text_texture, nullptr, &textDst);

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
	
	
	text = TTF_RenderText_Solid( font, "Hello World!", color );
    if ( !text ) {
        printf("SDL could not initialize! SDL Error: %s\n", TTF_GetError());
        success = false;
    }
    text_texture = SDL_CreateTextureFromSurface( renderer, text );
        
    
    SDL_RenderCopy( renderer, text_texture, NULL, &textDst );
    return success;
}
