#include "game.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>

void blocklike::Game::loop() {
	while(window.isOpen()) {
		pollEvents();
		update();
		draw();
	}
}

void blocklike::Game::stopGame() {
	logger.print("Closing game\n");
	
	window.close();
}

void blocklike::Game::startGame() {
	// Creating Logger
	logger = blocklike::Logger();

	// Setting up window
	logger.print("Setting up window\n");
	window.create(sf::VideoMode(1280, 720), "Blocklike", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i());
	window.setMouseCursorVisible(false);

	// Setting framerate limit
	logger.print("Setting framerate limit to 60\n");
	window.setFramerateLimit(60);

	// Setting up keys vector
	logger.print("Reserving space for keysDown vector");
	for(int i = 0; i < sf::Keyboard::KeyCount; i++) keysDown.push_back(false);

	// Creating player
	logger.print("Creating player\n");
	player = blocklike::Player();

	// Creating test blocks
	logger.print("Creating test block(s)\n");
	for (int x = -10; x < 10; x++) {
		for(int z = -10; z < 10; z++) {
			blocks.push_back(Block(x, 1, z));
		}
	}


	// Starting game loop
	logger.print("Starting game loop\n");
	loop();
}

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