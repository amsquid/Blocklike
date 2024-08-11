#include "game.hpp"
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

void blocklike::Game::update() {
	// Input
	player.velocity = sf::Vector3f();

	if(keysDown[sf::Keyboard::W]) player.velocity.z = -0.05f;
	if(keysDown[sf::Keyboard::S]) player.velocity.z = 0.05f;
	if(keysDown[sf::Keyboard::A]) player.velocity.x = 0.05f;
	if(keysDown[sf::Keyboard::D]) player.velocity.x = -0.05f;

	if(keysDown[sf::Keyboard::Up]) camera.rotation.y -= 0.05f;
	if(keysDown[sf::Keyboard::Down]) camera.rotation.y += 0.05f;
	if(keysDown[sf::Keyboard::Left]) camera.rotation.x -= 0.05f;
	if(keysDown[sf::Keyboard::Right]) camera.rotation.x += 0.05f;

	if(keysDown[sf::Keyboard::Escape]) stopGame();

	// Moving entities
	std::vector<blocklike::Entity>::iterator entityIt;

	for(entityIt = entities.begin(); entityIt < entities.end(); entityIt++) {
		entityIt->move();		
	}

	player.move();

	// Setting camera position
	camera.position = addVector3(player.position, sf::Vector3f(0, 2.0f, 0));
}