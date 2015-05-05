#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include <vector>

#include <GL/glew.h>

#include "gfx/sprite.hpp"
#include "gfx/free_image_texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gfx {
	class SpriteBatch {
		public:
			GLuint vao, vbo;
			unsigned int max, current;
			glm::vec4 defaultUV;
			std::vector<float> tempBuffer;

			SpriteBatch();
			SpriteBatch(unsigned int);
			~SpriteBatch();

			void initialize(int, int);

			//void draw(const glm::vec2&);
			//void draw(const glm::vec2&, float);
			void draw(const glm::vec2&, float, const glm::vec4&);

			void drawAll();
	};
}

#endif //SPRITE_BATCH_HPP
