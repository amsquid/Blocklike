#include "game.hpp"
#include <SFML/Window/Event.hpp>

void blocklike::Game::pollEvents() {
	sf::Event event;

	while(window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			stopGame();
		}
	}
}