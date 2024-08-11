#include "entity.hpp"

void blocklike::Player::setForwardAndVelocity(float horizontal, float vertical, float direction) {
	forwardVector.x = vertical * std::cos(direction);
	forwardVector.y = vertical * std::sin(direction);

	rightVector.x = horizontal * std::cos(direction - (3.14f / 2)) * 25.0f;
	rightVector.y = horizontal * std::sin(direction - (3.14f / 2)) * 25.0f;


	velocity.x = forwardVector.y + rightVector.y * speed;
	velocity.z = forwardVector.x + rightVector.x * speed;
}