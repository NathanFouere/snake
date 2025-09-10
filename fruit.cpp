#include <cstdlib>
#include <fruit.hpp>

// todo doit etre reorganiser ici
Fruit::Fruit() : Entity(rand() % 201, rand() % 201, false, false) {
}
