#ifndef GAME_HPP
#define GAME_HPP

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

#include "gfx/renderer.hpp"
#include "gfx/shader_uniforms.hpp"
#include "gfx/batch.hpp"
#include "gfx/font.hpp"
#include "gfx/mesh.hpp"
#include "gfx/mesh_loader.hpp"
#include "gfx/texture.hpp"
#include "gfx/texture_loader.hpp"
#include "gfx/shader.hpp"
#include "gfx/framebuffer.hpp"

#include "sound/sound_player.hpp"
#include "sound/sound.hpp"

#include "net/server.hpp"

namespace mg {
	class Game {
		protected:
			mg::SDL2Window _window;
			mg::SDL2Keyboard _keyboard;
			mg::SDL2Mouse _mouse;

			mg::Renderer _renderer;
			mg::Font _font;
			mg::TextureLoader _textureLoader;
			mg::MeshLoader _meshLoader;

			std::shared_ptr<mg::FrameBuffer> _fbo;
			std::shared_ptr<mg::ShaderUniforms> _uniforms;

			std::shared_ptr<mg::Batch> _worldBatch;
			std::shared_ptr<mg::Texture> _worldTexture;
			std::shared_ptr<mg::Shader> _worldShader;

			std::shared_ptr<mg::Shader> _screenShader;
			std::shared_ptr<mg::Batch> _screenBatch;
			std::shared_ptr<mg::Mesh> _screenMesh;

			mg::SoundPlayer _soundPlayer;
			mg::Sound _sound;

			mg::Player _player;
			mg::World _world;

			mg::Server _server;

			int _lastKey, _timesRendered;
			bool _wireframe, _windowIsFocused;
			std::clock_t _lastTime, _currentTime;
		public:
			Game();
			~Game();

			bool load();
			bool run();
	};
}

#endif //GAME_HPP
