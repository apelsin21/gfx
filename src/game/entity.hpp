#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/glm.hpp>

namespace mg {
	class Entity {
		protected:
			glm::vec3 _position, _scale, _rotation;
		public:
			glm::vec3 getPosition() {
				return _position;
			}
			glm::vec3 getScale() {
				return _scale;
			}

			void setPosition(const glm::vec3& p) {
				_position = p;
			}
			void setScale(const glm::vec3& s) {
				_scale = s;
			}
	};
}

#endif //ENTITY_HPP
