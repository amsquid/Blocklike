#include "../blocks/block.hpp"
#include "../logger.hpp"

#include <SFML/Window.hpp>

#include <vector>

namespace blocklike {
	class Game {
		public:
			void startGame();
			void stopGame();

			std::vector<blocklike::Block> blocks;

			blocklike::Logger logger;

		private:
			void draw();
			void update();
			void pollEvents();
			void loop();

			sf::Window window;

	};
}