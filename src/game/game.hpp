#include "../blocks/block.hpp"
#include "../entity/entity.hpp"

#include "../logger.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
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

			blocklike::Logger logger;

			blocklike::Camera camera;
			blocklike::Player player;

		private:
			void draw();
			void update();
			void pollEvents();
			void loop();

			sf::Vector3f addVector3(sf::Vector3f first, sf::Vector3f second);
			sf::Vector3f addVector3(sf::Vector3i first, sf::Vector3f second);
			sf::Vector3f addVector3(sf::Vector3f first, sf::Vector3i second);
			sf::Vector3f addVector3(sf::Vector3i first, sf::Vector3i second);

			sf::Vector2f project(sf::Vector3f position, sf::Vector3f off);
			sf::Vector2f project(sf::Vector3i position, sf::Vector3f off);

			sf::RenderWindow window;

	};
}