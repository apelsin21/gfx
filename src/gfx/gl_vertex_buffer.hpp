#ifndef GL_VERTEX_BUFFER
#define GL_VERTEX_BUFFER

#include <cstdio>
#include <vector>

#include <epoxy/gl.h>

namespace mg {
	class GLVertexBuffer {
		protected:
			std::vector<float> _vertices;
			unsigned int _numVertices, _maxVertices, _vbo;
			int _usage;
		public:
			GLVertexBuffer(unsigned int, bool);
			~GLVertexBuffer();

			unsigned int getMaxVertices() const;
			unsigned int getGLHandle() const;

			void bind() const;
			void unbind() const;

			bool setVertices(const std::vector<float>&);
			bool updateVertices(const std::vector<float>&, unsigned int);

			unsigned int getNumTriangles() const;
	};
}

#endif //GL_VERTEX_BUFFER
