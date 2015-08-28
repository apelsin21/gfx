#ifndef WORLD_HPP
#define WORLD_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <map>

#include <glm/gtc/noise.hpp>
#include <glm/gtx/norm.hpp>

#include "gfx/gl_vertex_buffer.hpp"
#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"

#include "game/marching_cubes.hpp" 

namespace mg {
	class World {
		protected:
			static constexpr double _isoLevel = 0.0;
			static constexpr int _numX = 64, _numY = 64, _numZ = 64;
			static constexpr int _numVoxels = _numX * _numY * _numZ;
			static constexpr float _scale = 0.1f;
			float scale;

			std::vector<float> _vertices;
			std::vector<GRIDCELL> _voxels;
			mg::GLVertexBuffer _buffer;

			bool _generatedVoxels, _generatedVertices;

			float _calcDensity(const glm::vec3&) const;

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
