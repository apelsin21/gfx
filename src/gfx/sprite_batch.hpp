#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include <vector>

#include <epoxy/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gfx/texture.hpp"
#include "gfx/font.hpp"

namespace mg {
	class SpriteBatch {
		public:
			GLuint vao, vbo;
			unsigned int max, current;
			glm::vec4 defaultUV;
			float* tempBuffer;

			SpriteBatch();
			SpriteBatch(unsigned int);
			~SpriteBatch();

			bool initialize(int, int);

			void draw(const glm::vec2&, const glm::vec2&, const glm::vec4&);
			void draw(const std::wstring&, mg::Font&, const glm::vec2&);

			void drawAll(unsigned int);
	};
}

#endif //SPRITE_BATCH_HPP
