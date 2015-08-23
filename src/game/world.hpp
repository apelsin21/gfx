#ifndef WORLD_HPP
#define WORLD_HPP

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include <glm/gtc/noise.hpp>

#include "gfx/gl_vertex_buffer.hpp"
#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"

#include "game/marching_cubes.hpp" 

namespace mg {
	class World {
		protected:
			std::vector<float> _vertices;
			mg::GLVertexBuffer _buffer;

			float _calcDensity(const glm::vec3&) const;
		public:
			World();
			~World();

			bool generate();

			const mg::GLVertexBuffer& getBuffer() const;
			std::vector<float> getVertices() const;

			std::vector<float> polygonize(GRIDCELL, double);
	};
}

#endif //WORLD_HPP
