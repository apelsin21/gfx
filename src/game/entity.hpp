#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/glm.hpp>

namespace mg {
	class Entity {
		protected:
			glm::vec3 pos, scale;
		public:
			virtual glm::vec3 getPosition() const = 0;
			virtual glm::vec3 getScale() const = 0;

			virtual void setPosition(const glm::vec3&) = 0;
			virtual void setScale(const glm::vec3&) = 0;
	};
}

#endif //ENTITY_HPP
