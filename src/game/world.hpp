#ifndef WORLD_HPP
#define WORLD_HPP

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include <glm/gtc/noise.hpp>
#include <glm/gtx/norm.hpp>

#include "gfx/gl_vertex_buffer.hpp"
#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"

#include "game/marching_cubes.hpp" 

namespace mg {
	class World {
		protected:
			std::vector<float> _vertices;
			mg::GLVertexBuffer _buffer;
			std::vector<GRIDCELL> _voxels;

			float _calcDensity(const glm::vec3&) const;
			glm::vec3 _calcNormal(const glm::vec3&) const;
		public:
			World();
			~World();

			bool generate();

			const mg::GLVertexBuffer& getBuffer() const;
			std::vector<float> getVertices() const;
	};
}

#endif //WORLD_HPP
