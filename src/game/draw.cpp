#include "game.hpp"
#include "quad.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
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
	// Drawing blocks
	sf::VertexArray vertices(sf::Quads, (blocks.size() * 6) * 4);

	std::vector<blocklike::Block>::iterator blockIt;
	std::map<float, blocklike::Quad2, std::less<float>> quadsSorted;

	window.clear(sf::Color::Black);

	int i = 0;

	std::map<float, Quad, std::greater<float>> offQuads;

	for(blockIt = blocks.begin(); blockIt != blocks.end(); blockIt++) {
		// Getting block data
		sf::Vector3i position = blockIt->position;

		sf::Vector3f camOff = addVector3(position, mulVector3(camera.position, -1));

		// Offset coordinates

		// TOP FACE
		if(!blockAt(as3i(addVector3(position, sf::Vector3f(0, -1, 0))))) {
			float distance1 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(0.5, -1, 0.5)));

			offQuads[distance1].position[0] = addVector3(camOff, sf::Vector3f(0, -1, 0));
			offQuads[distance1].position[1] = addVector3(camOff, sf::Vector3f(0, -1, 1));
			offQuads[distance1].position[2] = addVector3(camOff, sf::Vector3f(1, -1, 1));
			offQuads[distance1].position[3] = addVector3(camOff, sf::Vector3f(1, -1, 0));
		}


		// BOTTOM FACE AT ORIGIN
		if(!blockAt(as3i(addVector3(position, sf::Vector3f(0, 1, 0))))) {
			float distance2 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(0.5, 0, 0.5)));

			offQuads[distance2].position[0] = addVector3(camOff, sf::Vector3f(0, 0, 0));
			offQuads[distance2].position[1] = addVector3(camOff, sf::Vector3f(0, 0, 1));
			offQuads[distance2].position[2] = addVector3(camOff, sf::Vector3f(1, 0, 1));
			offQuads[distance2].position[3] = addVector3(camOff, sf::Vector3f(1, 0, 0));
		}

		// BACK FACE
		if(!blockAt(as3i(addVector3(position, sf::Vector3f(0, 0, -1))))) {
			float distance3 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(0.5, -.5, 0)));

			offQuads[distance3].position[0] = addVector3(camOff, sf::Vector3f(0, 0, 0));
			offQuads[distance3].position[1] = addVector3(camOff, sf::Vector3f(1, 0, 0));
			offQuads[distance3].position[2] = addVector3(camOff, sf::Vector3f(1, -1, 0));
			offQuads[distance3].position[3] = addVector3(camOff, sf::Vector3f(0, -1, 0));
		}

		// FRONT FACE
		if(!blockAt(as3i(addVector3(position, sf::Vector3f(0, 0, 1))))) {
			float distance4 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(0.5, -.5, 1)));

			offQuads[distance4].position[0] = addVector3(camOff, sf::Vector3f(0, 0, 1));
			offQuads[distance4].position[1] = addVector3(camOff, sf::Vector3f(1, 0, 1));
			offQuads[distance4].position[2] = addVector3(camOff, sf::Vector3f(1, -1, 1));
			offQuads[distance4].position[3] = addVector3(camOff, sf::Vector3f(0, -1, 1));
		}

		// RIGHT FACE
		if(!blockAt(as3i(addVector3(position, sf::Vector3f(1, 0, 0))))) {
			float distance5 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(1, -.5, .5)));

			offQuads[distance5].position[0] = addVector3(camOff, sf::Vector3f(1, 0, 0));
			offQuads[distance5].position[1] = addVector3(camOff, sf::Vector3f(1, 0, 1));
			offQuads[distance5].position[2] = addVector3(camOff, sf::Vector3f(1, -1, 1));
			offQuads[distance5].position[3] = addVector3(camOff, sf::Vector3f(1, -1, 0));
		}

		// LEFT FACE
		if(!blockAt(as3i(addVector3(position, sf::Vector3f(-1, 0, 0))))) {
			float distance6 = distanceFrom(camera.position, addVector3(position, sf::Vector3f(0, -.5, .5)));

			offQuads[distance6].position[0] = addVector3(camOff, sf::Vector3f(0, 0, 0));
			offQuads[distance6].position[1] = addVector3(camOff, sf::Vector3f(0, 0, 1));
			offQuads[distance6].position[2] = addVector3(camOff, sf::Vector3f(0, -1, 1));
			offQuads[distance6].position[3] = addVector3(camOff, sf::Vector3f(0, -1, 0));
		}
	}

	std::map<float, Quad>::iterator it;

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
	}

	window.draw(vertices);

	// Drawing debug info
	sf::Text quadsText;
	sf::Text posText;
	sf::Text rotationText;

	quadsText.setFont(mainFont);
	posText.setFont(mainFont);
	rotationText.setFont(mainFont);

	quadsText.setString(std::to_string(i) + " quad(s) drawn");
	posText.setString("POSITION X:" + std::to_string(player.position.x) + " Y:" + std::to_string(player.position.y) + " Z:" + std::to_string(player.position.z));
	rotationText.setString("ROTATION X:" + std::to_string(camera.rotation.x) + " Y:" + std::to_string(camera.rotation.y));

	quadsText.setFillColor(sf::Color::White);
	posText.setFillColor(sf::Color::White);
	rotationText.setFillColor(sf::Color::White);

	posText.setPosition(sf::Vector2f(0, 30.0f));
	rotationText.setPosition(sf::Vector2f(0, 60.0f));

	window.draw(quadsText);
	window.draw(posText);
	window.draw(rotationText);

	window.display();
}