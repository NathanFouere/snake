#include "fruit.hpp"
#include <cstdlib>

Fruit::Fruit() : Entity(rand() % 201, rand() % 201, 50, 50) {
    
}