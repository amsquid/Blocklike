#include "game.hpp"
#include <SFML/System/Vector3.hpp>
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
	logger.println("Closing game");
	
	window.close();
}

void blocklike::Game::startGame() {
	// Creating Logger
	logger = blocklike::Logger();

	// Setting up window
	logger.println("Setting up window");
	window.create(sf::VideoMode(1280, 720), "Blocklike", sf::Style::Titlebar | sf::Style::Close);

	// Creating player
	logger.println("Creating player");
	player = blocklike::Player();

	// Creating test blocks
	logger.println("Creating test block(s)");
	blocks.push_back(blocklike::Block(0, 1, 1));
	blocks.push_back(blocklike::Block(1, 1, 1));
	blocks.push_back(blocklike::Block(2, 1, 1));


	// Starting game loop
	logger.println("Starting game loop");
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