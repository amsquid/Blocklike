#include <SFML/System/Vector3.hpp>

namespace blocklike {
	class Block {
		public:
			Block(int x, int y, int z) {
				position = sf::Vector3i(x, y, z);
			}

			Block() {}

			sf::Vector3i position;
	};
}
