#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP

#include <cstdio>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <epoxy/gl.h>

#include "gfx/gl_shader.hpp"
#include "gfx/gl_texture.hpp"
#include "gfx/renderer.hpp"
#include "gfx/batch.hpp"
#include "gfx/color.hpp"
#include "gfx/mesh.hpp"
#include "gfx/shader_uniforms.hpp"

namespace mg {
	class GLRenderer : public Renderer {
		protected:
			GLuint _vao;

			int _posLocation, _uvLocation, _colorLocation, _normalLocation;
			static constexpr const char* _posName = "v_pos";
			static constexpr const char* _uvName = "v_uv";
			static constexpr const char* _colorName = "v_color";
			static constexpr const char* _normalName = "v_normal";

			glm::vec2 _res;
			mg::Color _clearColor;
		public:
			GLRenderer();
			~GLRenderer();

			void setClearColor(const mg::Color&);
			mg::Color getClearColor() const;

			void setSize(const glm::vec2&);
			glm::vec2 getSize() const;

			bool render(const std::shared_ptr<mg::Batch>&);
	};
}

#endif //GL_RENDERER_HPP
