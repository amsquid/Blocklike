#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
namespace blocklike {
	class Quad {
		public:
			sf::Vector3f position[4]; // Corner positions
	};

	class Quad2 {
		public:
			sf::Vector2f position[4];
	};
}
