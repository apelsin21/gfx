#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <cstdio>
#include <exception>

#include "core/sdl2_window.hpp"
#include "core/sdl2_keyboard.hpp"
#include "core/sdl2_mouse.hpp"
#include "core/keyboard_keys.hpp"

#include "game/level.hpp"

#include "gfx/font.hpp"
#include "gfx/free_image_texture_loader.hpp"
#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"
#include "gfx/sprite_batch.hpp"

namespace mg {
	class Game {
		protected:
			mg::SDL2Window window;
			mg::SDL2Keyboard keyboard;
			mg::SDL2Mouse mouse;

			mg::Level level;

			mg::SpriteBatch batch;

			mg::GLTexture texture;
			mg::GLShader shader;

			mg::FreeImageTextureLoader fiTexLoader;

			glm::vec2 pos;
		public:
			Game();
			~Game();

			bool load();
			void run();
	};
}

#endif //GAME_HPP
