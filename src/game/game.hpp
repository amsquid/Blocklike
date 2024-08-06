#include "../blocks/block.hpp"
#include "../entity/entity.hpp"

#include "../logger.hpp"

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

		private:
			void draw();
			void update();
			void pollEvents();
			void loop();

			sf::Window window;

	};
}