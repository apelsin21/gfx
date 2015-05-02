#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <cstring>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/type_aligned.hpp>

#include "gfx/vertex.hpp"
#include "gfx/color.hpp"
#include "gfx/free_image_texture.hpp"

namespace gfx {
    class Sprite {
		public:
			gfx::Color color;
			gfx::FreeImageTexture texture;
			glm::vec2 position;
			GLuint vbo, vao;

			Sprite(int, int);
			~Sprite();

			void draw();
    };
}

#endif //SPRITE_HPP
