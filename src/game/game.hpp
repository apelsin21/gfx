#ifndef GAME_HPP
#define GAME_HPP

#include <exception>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <epoxy/gl.h>

#include "core/keyboard_keys.hpp"
#include "core/sdl2_keyboard.hpp"
#include "core/sdl2_window.hpp"
#include "core/sdl2_mouse.hpp"

#include "game/player.hpp"
#include "game/world.hpp"

#include "gfx/gl_vertex_buffer.hpp"
#include "gfx/gl_renderer.hpp"
#include "gfx/gl_shader.hpp"

#include "gfx/shader_uniforms.hpp"
#include "gfx/batch.hpp"
#include "gfx/font.hpp"
#include "gfx/color.hpp"
#include "gfx/mesh.hpp"
#include "gfx/mesh_loader.hpp"
#include "gfx/texture.hpp"
#include "gfx/texture_loader.hpp"

#include "sound/sound_player.hpp"
#include "sound/sound.hpp"

namespace mg {
	class Game {
		protected:
			mg::SDL2Window _window;
			mg::SDL2Keyboard _keyboard;
			mg::SDL2Mouse _mouse;

			mg::GLRenderer _renderer;
			mg::Font _font;
			mg::TextureLoader _textureLoader;
			mg::MeshLoader _meshLoader;

			std::shared_ptr<mg::ShaderUniforms> _uniforms;

			std::shared_ptr<mg::Batch> _worldBatch;
			std::shared_ptr<mg::Texture> _worldTexture;
			std::shared_ptr<mg::GLShader> _worldShader;

			std::shared_ptr<mg::Batch> _jeepBatch;
			std::shared_ptr<mg::Mesh> _jeepMesh;
			std::shared_ptr<mg::Texture> _jeepTexture;
			std::shared_ptr<mg::GLShader> _jeepShader;

			mg::SoundPlayer _soundPlayer;
			mg::Sound _sound;

			mg::Player _player;
			mg::World _world;

			int _lastKey, _timesRendered;
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
