#include <memory>
#include <game.hpp>

int main(int argc, char* args[]) {
    auto game = std::make_unique<Game>();
    game->gameLoop();
    return 0;
}
