#include "../blocks/block.hpp"
#include "../entity/entity.hpp"

#include "../logger.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window.hpp>

#include <vector>

namespace blocklike {
	class Game {
		public:
			void startGame();
			void stopGame();

			std::vector<blocklike::Block> blocks;
			std::vector<blocklike::Entity> entities;
			std::vector<bool> keysDown;

			blocklike::Logger logger;

			blocklike::Camera camera;
			blocklike::Player player;

			sf::Vector2i mouseDelta;

			float cameraSensitivity = 0.001f;

		private:
			void draw();
			void update();
			void pollEvents();
			void loop();

			sf::Vector3f addVector3(sf::Vector3f first, sf::Vector3f second);
			sf::Vector3f addVector3(sf::Vector3i first, sf::Vector3f second);
			sf::Vector3f addVector3(sf::Vector3f first, sf::Vector3i second);
			sf::Vector3f addVector3(sf::Vector3i first, sf::Vector3i second);

			sf::Vector3f mulVector3(sf::Vector3f first, float second);

			float distanceFrom(sf::Vector3f origin, sf::Vector3f other);

			sf::Vector3f rotateWithCamera(sf::Vector3f position);

			sf::Vector2f project(sf::Vector3f position, float distance);
			sf::Vector2f project(sf::Vector3i position, float distance);

			float calculateDepthForSorting(const sf::Vector3f cameraPos, const sf::Vector3f blockPos, const sf::Vector2f cameraRotation);

			bool insideScreen(float x, float y);

			sf::RenderWindow window;

	};
}