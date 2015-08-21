#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP

#include <cstdio>

#include <glm/glm.hpp>

#include <epoxy/gl.h>

#include "gfx/renderer.hpp"
#include "gfx/gl_shader.hpp"
#include "gfx/gl_vertex_buffer.hpp"

namespace mg {
	class GLRenderer : public Renderer {
		protected:
			GLuint _vao;

			int _posLocation, _uvLocation, _colorLocation, _normalLocation;
			static constexpr const char* _posName = "v_pos";
			static constexpr const char* _uvName = "v_uv";
			static constexpr const char* _colorName = "v_color";
			static constexpr const char* _normalName = "v_normal";
		public:
			GLRenderer();
			~GLRenderer();

			bool render(const mg::GLShader&, const mg::GLVertexBuffer&);
	};
}

#endif //GL_RENDERER_HPP
