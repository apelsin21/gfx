#ifndef WORLD_HPP
#define WORLD_HPP

#include <cstdio>
#include <string>
#include <vector>

#include "gfx/gl_vertex_buffer.hpp"
#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"

namespace mg {
	class World {
		protected:
			std::vector<float> _vertices;
			mg::GLVertexBuffer _buffer;
		public:
			World();
			~World();

			bool generate();

			const mg::GLVertexBuffer& getBuffer() const;
			std::vector<float> getVertices() const;
	};
}

#endif //WORLD_HPP
