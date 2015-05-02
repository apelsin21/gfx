#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include <GL/glew.h>

#include "gfx/sprite.hpp"
#include "gfx/free_image_texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gfx {
	class SpriteBatch {
		public:
			GLuint pos_vbo, uv_vbo, vao;
			unsigned int max, current;

			SpriteBatch();
			SpriteBatch(unsigned int);
			~SpriteBatch();

			void initialize(int, int);

			void draw(gfx::Texture&, const glm::vec2&);
			void draw(gfx::Texture&, const glm::vec2&, float);

			void drawAll();
	};
}

#endif //SPRITE_BATCH_HPP
