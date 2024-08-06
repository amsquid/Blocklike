#include "game.hpp"
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

	// Creating test blocks
	blocks.push_back(blocklike::Block(0, 0, 5));

	// Starting game loop
	logger.println("Starting game loop");
	loop();
}