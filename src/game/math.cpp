#include "game.hpp"

// Projections
sf::Vector2f blocklike::Game::project(sf::Vector3f position) {
	return sf::Vector2f(
		(position.x * camera.fov) / (position.z + camera.fov * .1f),
		(position.y * camera.fov) / (position.z + camera.fov * .1f)
	);
}

sf::Vector2f blocklike::Game::project(sf::Vector3i position) {
	return sf::Vector2f(
		(position.x * camera.fov) / (position.z + camera.fov * .1f),
		(position.y * camera.fov) / (position.z + camera.fov * .1f)
	);
}

// Rotations
sf::Vector3f blocklike::Game::rotateWithCamera(sf::Vector3f position) {
	// X Rotation
	float xr1 = (position.x * std::cos(camera.rotation.x)) - (position.z * sin(camera.rotation.x));
	float yr1 = position.y;
	float zr1 = (position.x * std::sin(camera.rotation.x)) + (position.z * cos(camera.rotation.x));

	// Y rotation
	float xr2 = xr1;
	float yr2 = (yr1 * std::cos(camera.rotation.y)) - (zr1 * std::sin(camera.rotation.y));
	float zr2 = (yr1 * std::sin(camera.rotation.y)) + (zr1 * std::cos(camera.rotation.y));

	// Return
	return sf::Vector3f(xr2, yr2, zr2);
}

// Adding Vectors
sf::Vector3f blocklike::Game::addVector3(sf::Vector3f first, sf::Vector3f second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}

sf::Vector3f blocklike::Game::addVector3(sf::Vector3i first, sf::Vector3f second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}

sf::Vector3f blocklike::Game::addVector3(sf::Vector3f first, sf::Vector3i second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}

sf::Vector3f blocklike::Game::addVector3(sf::Vector3i first, sf::Vector3i second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}