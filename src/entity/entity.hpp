#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>

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
			float near = 0.1f;
	};
	class Player : public Entity {
		public:
			float health;

			sf::Vector2f forwardVector;
			sf::Vector2f rightVector;

			float speed = 0.05f;

			void setForwardAndVelocity(float horizontal, float vertical, float direction);
	};
}