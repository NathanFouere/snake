#include "game.hpp"

int main(int argc, char* args[]) {
    Game* game = new Game();
    game->gameLoop();
    return 0;
}
