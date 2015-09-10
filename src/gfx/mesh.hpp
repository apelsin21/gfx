#ifndef MESH_HPP
#define MESH_HPP

#include <memory>
#include <vector>
#include <stdexcept>

#include <epoxy/gl.h>

#include "gfx/vertex_format.hpp"

namespace mg {
	class Mesh {
		protected:
			mg::VertexFormat _format;

			GLuint _vbo, _ibo;
			unsigned int _vboSize, _iboSize, _numFloats, _numInts;
		public:
			Mesh();
			~Mesh();

			void setVertexFormat(mg::VertexFormat);
			mg::VertexFormat getVertexFormat() const;

			bool uploadVertexData(const std::vector<float>&);
			bool uploadIndexData(const std::vector<int>&);

			GLuint getVertexBuffer() const;
			GLuint getIndexBuffer() const;

			unsigned int getNumFloats() const;
			unsigned int getNumInts() const;
			unsigned int getVertexBufferSize() const;
			unsigned int getIndexBufferSize() const;
	};
}

#endif //MESH_HPP
