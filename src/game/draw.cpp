#include "game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <cmath>

bool blocklike::Game::insideScreen(float x, float y) {
	return 
		x < window.getSize().x && x > 0 &&
		y < window.getSize().y && y > 0;
}

void blocklike::Game::draw() {
	sf::VertexArray vertices(sf::Quads, (blocks.size() * 4) * 6);

	std::vector<blocklike::Block>::iterator blockIt;

	window.clear(sf::Color::Black);

	int i = 0;

	for(blockIt = blocks.begin(); blockIt < blocks.end(); blockIt++) {
		// Getting block data		
		sf::Vector3i position = blockIt->position;

		sf::Vector3f camOff = addVector3(position, camera.position);

		// Offset coordinates
		sf::Vector3f off1 = addVector3(camOff, sf::Vector3f(0, -1, 0));
		sf::Vector3f off2 = addVector3(camOff, sf::Vector3f(0, -1, 1));
		sf::Vector3f off3 = addVector3(camOff, sf::Vector3f(1, -1, 1));
		sf::Vector3f off4 = addVector3(camOff, sf::Vector3f(1, -1, 0));

		// Rotation coordinates
		sf::Vector3f rot1 = rotateWithCamera(off1);
		sf::Vector3f rot2 = rotateWithCamera(off2);
		sf::Vector3f rot3 = rotateWithCamera(off3);
		sf::Vector3f rot4 = rotateWithCamera(off4);

		// Projection coordinates
		sf::Vector2f proj1 = project(rot1);
		sf::Vector2f proj2 = project(rot2);
		sf::Vector2f proj3 = project(rot3);
		sf::Vector2f proj4 = project(rot4);

		// Drawing coordinates
		float x1Draw = (window.getSize().x / 2) + (proj1.x * 100.0f);
		float y1Draw = (window.getSize().y / 2) + (proj1.y * 100.0f);

		float x2Draw = (window.getSize().x / 2) + (proj2.x * 100.0f);
		float y2Draw = (window.getSize().y / 2) + (proj2.y * 100.0f);

		float x3Draw = (window.getSize().x / 2) + (proj3.x * 100.0f);
		float y3Draw = (window.getSize().y / 2) + (proj3.y * 100.0f);

		float x4Draw = (window.getSize().x / 2) + (proj4.x * 100.0f);
		float y4Draw = (window.getSize().y / 2) + (proj4.y * 100.0f);

		if(
			(
				!insideScreen(x1Draw, y1Draw) &&
				!insideScreen(x2Draw, y2Draw) &&
				!insideScreen(x3Draw, y3Draw) &&
				!insideScreen(x4Draw, y4Draw)
			) ||
			(
				rot1.z < 0 &&
				rot2.z < 0 &&
				rot3.z < 0 &&
				rot4.z < 0
			)
		) {
			continue;
		}

		// Adding to vertecies
		vertices[(i + 0) * 4 + 0].position = sf::Vector2f(x1Draw, y1Draw);
		vertices[(i + 0) * 4 + 1].position = sf::Vector2f(x2Draw, y2Draw);
		vertices[(i + 0) * 4 + 2].position = sf::Vector2f(x3Draw, y3Draw);
		vertices[(i + 0) * 4 + 3].position = sf::Vector2f(x4Draw, y4Draw);

		vertices[(i + 0) * 4 + 0].color = sf::Color::Magenta;
		vertices[(i + 0) * 4 + 1].color = sf::Color::Green;
		vertices[(i + 0) * 4 + 2].color = sf::Color::White;
		vertices[(i + 0) * 4 + 3].color = sf::Color::Yellow;

		// Adding index
		i++;
	}

	logger.print("Drawn ");
	logger.print(i);
	logger.print(" quads\n");

	window.draw(vertices);

	window.display();
}