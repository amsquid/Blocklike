#include "game.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <vector>

void blocklike::Game::update() {
	// Input
	float horizontal = 0.0f;
	float vertical = 0.0f;

	player.velocity = sf::Vector3f();

	if(keysDown[sf::Keyboard::W]) vertical = 0.05f;
	if(keysDown[sf::Keyboard::S]) vertical = -0.05f;
	if(keysDown[sf::Keyboard::A]) horizontal = -0.05f;
	if(keysDown[sf::Keyboard::D]) horizontal = 0.05f;

	player.setForwardAndVelocity(-horizontal, vertical, camera.rotation.x);

	if(keysDown[sf::Keyboard::Escape]) stopGame();

	// Moving entities
	std::vector<blocklike::Entity>::iterator entityIt;

	for(entityIt = entities.begin(); entityIt < entities.end(); entityIt++) {
		entityIt->move();		
	}

	player.move();

	// Mouse
	mouseDelta = sf::Vector2i(
		(window.getPosition().x - sf::Mouse::getPosition().x) + (window.getSize().x * 0.5f), 
		(window.getPosition().y - sf::Mouse::getPosition().y) + (window.getSize().y * 0.5f));

	// Locking mouse
	if(window.hasFocus())
		sf::Mouse::setPosition(
			sf::Vector2i((window.getSize().x / 2) + window.getPosition().x, (window.getSize().y / 2) + window.getPosition().y)
		);
	
	// Camera Rotation
	camera.rotation.x -= mouseDelta.x * cameraSensitivity;
	camera.rotation.y -= mouseDelta.y * cameraSensitivity;

	camera.rotation.y = std::clamp(camera.rotation.y, -1.5f, 1.5f);

	// Setting camera position
	camera.position = addVector3(player.position, sf::Vector3f(0, -2.0f, 0));	
}