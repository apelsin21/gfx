#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/glm.hpp>

namespace mg {
	class Entity {
		protected:
			glm::vec3 pos, scale;
		public:
			glm::vec3 getPosition() {
				return this->pos;
			}
			glm::vec3 getScale() {
				return this->scale;
			}

			void setPosition(const glm::vec3& p) {
				this->pos = p;
			}
			void setScale(const glm::vec3& s) {
				this->scale = s;
			}
	};
}

#endif //ENTITY_HPP
