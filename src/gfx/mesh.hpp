#ifndef MESH_HPP
#define MESH_HPP

#include <memory>
#include <vector>

#include <epoxy/gl.h>

#include "gfx/vertex_format.hpp"

namespace mg {
	class Mesh {
		protected:
			mg::VertexFormat _format;

			std::vector<float> _data;

			unsigned int _vbo;
		public:
			Mesh();
			~Mesh();

			void setVertexFormat(mg::VertexFormat);
			mg::VertexFormat getVertexFormat() const;

			bool setData(const std::vector<float>&);
			const std::vector<float>& getData() const;

			unsigned int getGLHandle() const;
	};
}

#endif //MESH_HPP
