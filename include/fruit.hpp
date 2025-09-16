#pragma once
#include <entity.hpp>
#include <snake.hpp>

class Fruit : public Entity {
    public:
        Fruit();
        explicit Fruit(const Snake& snake);
};
