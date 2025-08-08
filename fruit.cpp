#include <cstdlib>
#include <fruit.hpp>

Fruit::Fruit() : Entity(rand() % 201, rand() % 201, 50, 50) {
}
