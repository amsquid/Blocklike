#include "game.hpp"
#include <SFML/System/Vector3.hpp>
#include <algorithm>
#include <cmath>

// Distance
float blocklike::Game::distanceFrom(sf::Vector3f origin, sf::Vector3f other) {
	float dx = other.x - origin.x;
	float dy = other.y - origin.y;
	float dz = other.z - origin.z;

	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

float blocklike::Game::calculateDepthForSorting(const sf::Vector3f cameraPos, const sf::Vector3f blockPos, const sf::Vector2f cameraRotation) {
	sf::Vector3f cameraDir(
		std::cos(cameraRotation.y) * std::cos(cameraRotation.x),
		std::sin(cameraRotation.x),
		std::sin(cameraRotation.y) * std::cos(cameraRotation.x)
	);

	sf::Vector3f relativePos = blockPos - cameraPos;

	return (relativePos.x * cameraDir.x) +
		   (relativePos.y * cameraDir.y) +
		   (relativePos.z * cameraDir.z);
}

// Projections
sf::Vector2f blocklike::Game::project(sf::Vector3f position, float distance) {
	float aspect = window.getSize().x / window.getSize().y;

	float z = std::max(position.z, camera.near);

	return sf::Vector2f(
		((position.x / (z + distance)) * camera.fov * aspect),
		((position.y / (z + distance)) * camera.fov)
	);
}

sf::Vector2f blocklike::Game::project(sf::Vector3i position, float distance) {
	float aspect = window.getSize().x / window.getSize().y;

	float z = std::max((float) position.z, camera.near);

	return sf::Vector2f(
		((position.x / (z + distance)) * camera.fov * aspect),
		((position.y / (z + distance)) * camera.fov)
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

// Multiplying vectors
sf::Vector3f blocklike::Game::mulVector3(sf::Vector3f first, float second) {
	return sf::Vector3f(
		first.x * second,
		first.y * second,
		first.z * second
	);
}

// Inside Screen
bool blocklike::Game::insideScreen(float x, float y) {
	return 
		x < window.getSize().x && x > 0 &&
		y < window.getSize().y && y > 0;
}