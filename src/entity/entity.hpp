#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace blocklike {
	class Entity {
		public:
			sf::Vector3f position;
			sf::Vector2f rotation;

			sf::Vector3f velocity;

			void move();
	};

	class Camera : public Entity {
		public:
			float fov = 3.0f;
	};
	class Player : public Entity {
		public:
			float health;
	};
}