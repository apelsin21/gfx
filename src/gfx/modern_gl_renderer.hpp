#ifndef MODERN_GL_RENDERER_HPP
#define MODERN_GL_RENDERER_HPP

#include "gfx/renderer.hpp"
#include "gfx/gl_vertex_buffer.hpp"

#include "epoxy/gl.h"

namespace mg {
	class ModernGLRenderer {
		protected:
			GLuint _vao;
			GLint _maxTextureWidth, _maxTextureHeight;
		public:
			ModernGLRenderer();
			~ModernGLRenderer();

			void drawBuffer(mg::GLVertexBuffer&);
	};
}

#endif //MODERN_GL_RENDERER_HPP
