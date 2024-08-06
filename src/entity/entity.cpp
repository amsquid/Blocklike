#include "entity.hpp"

void blocklike::Entity::move() {
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;
}