#include "game.hpp"
#include "quad.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <cmath>
#include <cstdlib>
#include <functional>
#include <map>
#include <string>
#include <vector>

void blocklike::Game::draw() {
	sf::VertexArray vertices(sf::Quads, (blocks.size() * 4) * 6);

	std::vector<blocklike::Block>::iterator blockIt;
	std::map<float, blocklike::Block, std::less<float>> blocksSorted;

	window.clear(sf::Color::Black);

	int i = 0;
	int y = 0;

	for(blockIt = blocks.begin(); blockIt < blocks.end(); blockIt++) {
		sf::Vector3i position = blockIt->position;
		sf::Vector3f positionf = sf::Vector3f(position.x, position.y, position.z);

		float distance = std::abs((camera.position.x - positionf.x) + (camera.position.y - positionf.y) + (camera.position.z - positionf.z));

		logger.print(distance);
		logger.print("\n");

		blocksSorted[distance].position = position;
	
		y++;
	}

	logger.print("============\n");

	std::map<float, blocklike::Block>::iterator sortedIt;

	for(sortedIt = blocksSorted.begin(); sortedIt != blocksSorted.end(); sortedIt++) {
		// Getting block data
		sf::Vector3i position = sortedIt->second.position;

		sf::Vector3f camOff = addVector3(position, camera.position);

		// Offset coordinates
		std::map<float, Quad, std::greater<float>> offQuads;

		float distance1 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(0, 1, 0)));

		offQuads[distance1].position[0] = addVector3(camOff, sf::Vector3f(0, -1, 0));
		offQuads[distance1].position[1] = addVector3(camOff, sf::Vector3f(0, -1, 1));
		offQuads[distance1].position[2] = addVector3(camOff, sf::Vector3f(1, -1, 1));
		offQuads[distance1].position[3] = addVector3(camOff, sf::Vector3f(1, -1, 0));

		float distance2 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(0, 0, 0)));

		offQuads[distance2].position[0] = addVector3(camOff, sf::Vector3f(0, 0, 0));
		offQuads[distance2].position[1] = addVector3(camOff, sf::Vector3f(0, 0, 1));
		offQuads[distance2].position[2] = addVector3(camOff, sf::Vector3f(1, 0, 1));
		offQuads[distance2].position[3] = addVector3(camOff, sf::Vector3f(1, 0, 0));

		std::map<float, Quad>::iterator it;
		int x = 0;

		for(it = offQuads.begin(); it != offQuads.end(); it++) {


			// Rotation coordinates
			sf::Vector3f rot1 = rotateWithCamera(it->second.position[0]);
			sf::Vector3f rot2 = rotateWithCamera(it->second.position[1]);
			sf::Vector3f rot3 = rotateWithCamera(it->second.position[2]);
			sf::Vector3f rot4 = rotateWithCamera(it->second.position[3]);

			// Projection coordinates
			sf::Vector2f proj1 = project(rot1, 0.0f);
			sf::Vector2f proj2 = project(rot2, 0.0f);
			sf::Vector2f proj3 = project(rot3, 0.0f);
			sf::Vector2f proj4 = project(rot4, 0.0f);

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
			x++;
		}
	}

	window.setTitle("Blocklike | Drew " + std::to_string(i) + " quad(s)");

	window.draw(vertices);

	window.display();
}