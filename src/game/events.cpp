#include "game.hpp"
#include <SFML/Window/Event.hpp>

void blocklike::Game::pollEvents() {
	sf::Event event;

	while(window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			stopGame();
		}

		if(event.type == sf::Event::KeyPressed) {
			keysDown[event.key.code] = true;
		}

		if(event.type == sf::Event::KeyReleased) {
			keysDown[event.key.code] = false;
		}
	}
}