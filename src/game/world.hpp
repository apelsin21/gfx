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

#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"

#include "game/marching_cubes.hpp" 

namespace mg {
	class World {
		protected:
			double _isoLevel;
			int _numX, _numY, _numZ;
			int _numVoxels;
			float _voxelSize;

			std::vector<float> _voxels, _vertices;

			bool _generatedVoxels, _generatedVertices;

			float _calcDensity(const glm::vec3&) const;
		public:
			World();
			~World();

			bool generateVoxels();
			bool generateVertices();
			void reset();

			bool addVoxels(const glm::vec3&);
			bool removeVoxels(const glm::vec3&);
			bool setVoxel(unsigned int, float);
			bool setSphere(const glm::vec3&, unsigned int, float);
			unsigned int getIndex(const glm::vec3&) const;

			const std::vector<float>& getVertices() const;
	};
}

#endif //WORLD_HPP
