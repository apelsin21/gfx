#ifndef GL_VERTEX_BUFFER
#define GL_VERTEX_BUFFER

#include <cstdio>
#include <vector>

#include <epoxy/gl.h>

#include "gfx/vertex_format.hpp"

namespace mg {

	class GLVertexBuffer {
		protected:
			unsigned int _vbo, _numVertices, _maxVertices;
			int _usage;

			mg::VertexFormat _format;
		public:
			GLVertexBuffer();
			~GLVertexBuffer();

			unsigned int getNumVertices() const;
			unsigned int getMaxVertices() const;
			unsigned int getGLHandle() const;
			bool isStatic() const;
			mg::VertexFormat getFormat() const;

			void bind() const;
			void unbind() const;

			bool allocate(unsigned int, bool, mg::VertexFormat);
			bool update(const std::vector<float>&, bool, mg::VertexFormat);
			bool updateRegion(const std::vector<float>&, unsigned int, unsigned int);

			void clear();
	};
}

#endif //GL_VERTEX_BUFFER
