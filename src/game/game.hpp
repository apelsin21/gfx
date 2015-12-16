#ifndef GAME_HPP
#define GAME_HPP

#include <ctime>

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
			mg::SDL2Window 		m_window;
			mg::SDL2Keyboard 	m_keyboard;
			mg::SDL2Mouse 		m_mouse;

			mg::Renderer 	m_renderer;
			mg::Font 		m_font;

			mg::MeshLoader 					m_meshLoader;
			mg::TextureLoader 				m_textureLoader;
			std::shared_ptr<mg::Texture> 	m_worldTexture;

			std::shared_ptr<mg::Mesh> m_fontMesh;
			std::shared_ptr<mg::Mesh> m_screenMesh;

			std::shared_ptr<mg::FrameBuffer> 	m_fbo;
			std::shared_ptr<mg::ShaderUniforms> m_uniforms;

			std::shared_ptr<mg::Batch> m_screenBatch;
			std::shared_ptr<mg::Batch> m_worldBatch;

			std::shared_ptr<mg::Shader> m_worldShader;
			std::shared_ptr<mg::Shader> m_screenShader;

			mg::SoundPlayer m_soundPlayer;
			mg::Sound m_sound;

			mg::Player m_player;
			mg::World m_world;

			int m_lastKey, m_timesRendered;
			bool m_wireframe, m_windowIsFocused;
			std::clock_t m_lastTime, m_currentTime;
		public:
			Game();
			~Game();

			bool load();
			bool run();
	};
}

#endif //GAME_HPP
