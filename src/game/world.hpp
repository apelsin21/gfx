#ifndef WORLD_HPP
#define WORLD_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <chrono>

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
			std::unique_ptr<GRIDCELL[]> _voxels;
			mg::GLVertexBuffer _buffer;

			static constexpr int _numX = 32, _numY = 32, _numZ = 32;
			static constexpr int _numVoxels = _numX * _numY * _numZ;
			float _calcDensity(const glm::vec3&) const;

			bool _generatedVoxels, _generatedVertices;
		public:
			World();
			~World();

			bool generateVoxels();
			bool generateVertices();

			const mg::GLVertexBuffer& getBuffer() const;
			std::vector<float> getVertices() const;
	};
}

#endif //WORLD_HPP
