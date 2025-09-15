#include <constants.h>
#include <cstdlib>
#include <snake.hpp>
#include <fruit.hpp>

Fruit::Fruit() :
    Entity(rand() % (SCREEN_WIDTH - WIDTH_ENTITY), rand() % (SCREEN_HEIGHT - HEIGHT_ENTITY))
{}

Fruit::Fruit(const Snake& snake): Fruit() {
    bool hasFoundedPosition = false;

    while (false == hasFoundedPosition) {
        int x = rand() % (SCREEN_WIDTH - WIDTH_ENTITY);
        int y = rand() % (SCREEN_HEIGHT - HEIGHT_ENTITY);
        bool hasOneCollisionWithSnake = false;
        for (auto& e : snake.getEntities()) {
            if (true == e->checkCollisionWithPoint(x, y)) {
                hasOneCollisionWithSnake = true;
                break;
            }
        }
        if (false == hasOneCollisionWithSnake) {
            hasFoundedPosition = true;
            this->setX(x);
            this->setY(y);
        }
    }
}
