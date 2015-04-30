#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <GL/glew.h>

#include "gfx/sprite.hpp"
#include "gfx/free_image_texture.hpp"

namespace gfx {
	class SpriteManager {
		public:
			GLuint pos_vbo, uv_vbo, color_vbo, vao;
			unsigned int maxSprites, numSprites;

			SpriteManager();
			SpriteManager(unsigned int);
			~SpriteManager();

			void initialize(int, int, int);

			Sprite getSprite();
			void addSprite();
	};
}

#endif //SPRITE_MANAGER_HPP
