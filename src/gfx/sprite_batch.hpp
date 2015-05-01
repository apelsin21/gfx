#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include <GL/glew.h>

#include "gfx/sprite.hpp"
#include "gfx/free_image_texture.hpp"

namespace gfx {
	class SpriteBatch {
		public:
			GLuint pos_vbo, uv_vbo, color_vbo, vao;
			unsigned int maxSprites, numSprites;

			SpriteBatch();
			SpriteBatch(unsigned int);
			~SpriteBatch();

			void initialize(int, int, int);

			Sprite getSprite();
			void addSprite();
	};
}

#endif //SPRITE_BATCH_HPP
