#pragma once
#include <entity.hpp>
#include <snake.hpp>

class Fruit : public Entity {
    public:
        Fruit();
        Fruit(const Snake& snake);
};
