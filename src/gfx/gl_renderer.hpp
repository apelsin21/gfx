#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP

#include <cstdio>
#include <cstdilb>

#include <glm/glm.hpp>

#include <epoxy/gl.h>

#include "gfx/renderer.hpp"

#include "gfx/gl_shader.hpp"

namespace mg {
	class GLRenderer : public Renderer {
		protected:
			mg::GLShader _shader2D;

			unsigned int numRenderedVertices;
			GLuint _vao, _vbo;
			unsigned int _max, _current;

			glm::vec4 _defaultUV;

			float* _pTempBuffer;
		public:
			GLRenderer();
			~GLRenderer();

			bool queue2D(const glm::vec2&, const glm::vec2&, const glm::vec4&);

			bool render();
	};
}

#endif //GL_RENDERER_HPP
