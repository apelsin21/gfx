#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>

#include <glm/gtc/noise.hpp>
#include <glm/gtx/norm.hpp>

#include "gfx/vertex_format.hpp"
#include "gfx/mesh.hpp"

#include "game/marching_cubes.hpp" 

namespace mg {
	class World {
		protected:
			double _isoLevel;
			int _numX, _numY, _numZ;
			int _numVoxels;
			float _voxelSize;

			std::vector<float> _voxels, _vertices;
			std::shared_ptr<mg::Mesh> _mesh;

			bool _generatedVoxels, _generatedMesh;

			float _calcDensity(const glm::vec3&) const;
		public:
			World();
			~World();

			bool generateVoxels();
			bool generateMesh();
			void reset();

			bool addVoxels(const glm::vec3&);
			bool removeVoxels(const glm::vec3&);
			bool setVoxel(unsigned int, float);
			bool setSphere(const glm::vec3&, unsigned int, float);
			unsigned int getIndex(const glm::vec3&) const;

			std::shared_ptr<mg::Mesh> getMesh() const;
	};
}

#endif //WORLD_HPP
