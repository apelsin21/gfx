#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <cstdio>
#include <exception>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <epoxy/gl.h>

#include "core/sdl2_window.hpp"
#include "core/sdl2_keyboard.hpp"
#include "core/sdl2_mouse.hpp"
#include "core/keyboard_keys.hpp"

#include "game/player.hpp"
#include "game/world.hpp"

#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"
#include "gfx/gl_vertex_buffer.hpp"
#include "gfx/gl_renderer.hpp"
#include "gfx/font.hpp"

#include "sound/sound_player.hpp"
#include "sound/sound.hpp"

namespace mg {
	class Game {
		protected:
			mg::SDL2Window _window;
			mg::SDL2Keyboard _keyboard;
			mg::SDL2Mouse _mouse;

			mg::GLTexture _texture;
			mg::GLShader _shader;
			mg::GLRenderer _renderer;
			mg::GLVertexBuffer _buffer;

			mg::SoundPlayer _soundPlayer;
			mg::Sound _sound;
			
			mg::Font _font;

			mg::Player _player;
			mg::World _world;

			int _lastKey, _timesRendered;
			double _isoLevel;
			bool _wireframe, _windowIsFocused;
			std::clock_t _lastTime, _currentTime;
		public:
			Game();
			~Game();

			bool load();
			void run();
	};
}

#endif //GAME_HPP
