#ifndef GL_VERTEX_BUFFER
#define GL_VERTEX_BUFFER

#include <cstdio>
#include <vector>

#include <epoxy/gl.h>

namespace mg {
	class GLVertexBuffer {
		protected:
			unsigned int _vbo;
			int _usage;
			std::size_t _size;
		public:
			GLVertexBuffer();
			~GLVertexBuffer();

			std::size_t getSize() const;
			unsigned int getGLHandle() const;
			bool isStatic() const;

			void bind() const;
			void unbind() const;

			bool allocate(std::size_t, bool);
			bool update(const std::vector<float>&);
			bool updateRegion(const std::vector<float>&, std::size_t, std::size_t);
	};
}

#endif //GL_VERTEX_BUFFER
