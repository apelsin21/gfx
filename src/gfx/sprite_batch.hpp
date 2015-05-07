#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gfx/texture.hpp"
#include "gfx/font.hpp"

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
			void draw(const glm::vec2&, const glm::vec2&, const glm::vec4&);
			void drawString(const std::string&, gfx::Font&, const glm::vec2&, const glm::vec2&);

			void drawAll();
	};
}

#endif //SPRITE_BATCH_HPP
