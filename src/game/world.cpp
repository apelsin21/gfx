#include "game/world.hpp"

mg::World::World() {
	_generatedVoxels = false;
	_generatedMesh = false;

	_isoLevel = 0;
	_numX = 64;
	_numY = 64;
	_numZ = 64;
	_numVoxels = _numX*_numY*_numZ;
	_voxelSize = 0.1f;

	_mesh = std::shared_ptr<mg::Mesh>(new mg::Mesh());
	_mesh->setVertexFormat(mg::VertexFormat::PPPNNN);
}
mg::World::~World() {
}

bool mg::World::generateVoxels() {
	if(_generatedVoxels) {
		printf("World tried to regenerate voxels!\n");
		return false;
	}

	_voxels = std::vector<float>(_numVoxels);

	for(unsigned int x = 0; x < _numX; x++) {
		for(unsigned int y = 0; y < _numY; y++) {
			for(unsigned int z = 0; z < _numZ; z++) {
				_voxels[x * _numX * _numY + y * _numZ + z] = _calcDensity(glm::vec3(x*_voxelSize, y*_voxelSize, z*_voxelSize));
			}
		}
	}

	_generatedVoxels = true;

	return true;
}
bool mg::World::generateMesh() {
	if(!_generatedVoxels || _voxels.empty()) {
		printf("world tried to generate vertices from no voxels.\n");
	}

	const unsigned int numPossibleTriangles = _numVoxels*5;
	unsigned int totalTriangles = 0;
	unsigned int vertexIndex = 0;
	_vertices = std::vector<float>(numPossibleTriangles*18);

	std::array<TRIANGLE, 5> tempTriangles;
	GRIDCELL cell;

	for(unsigned int x = 0; x < _numX; x++) {
		for(unsigned int y = 0; y < _numY; y++) {
			for(unsigned int z = 0; z < _numZ; z++) {

				// Cell positions.
				cell.p[0] = glm::vec3(x * _voxelSize, y * _voxelSize, z * _voxelSize);
				cell.p[1] = glm::vec3(cell.p[0].x + _voxelSize, cell.p[0].y, 			  cell.p[0].z);
				cell.p[2] = glm::vec3(cell.p[1].x, 				cell.p[0].y + _voxelSize, cell.p[0].z);
				cell.p[3] = glm::vec3(cell.p[0].x, 				cell.p[2].y, 			  cell.p[0].z);
				cell.p[4] = glm::vec3(cell.p[0].x, 				cell.p[0].y, 			  cell.p[0].z + _voxelSize);
				cell.p[5] = glm::vec3(cell.p[1].x,				cell.p[0].y, 			  cell.p[4].z);
				cell.p[6] = glm::vec3(cell.p[1].x,				cell.p[2].y,			  cell.p[4].z);
				cell.p[7] = glm::vec3(cell.p[0].x,				cell.p[2].y,			  cell.p[4].z);

				// Cell values for each corner.
				cell.val[0] = _voxels[x     * _numX * _numY + y     * _numZ + z    ];
				cell.val[1] = _voxels[(x+1) * _numX * _numY + y     * _numZ + z    ];
				cell.val[2] = _voxels[(x+1) * _numX * _numY + (y+1) * _numZ + z    ];
				cell.val[3] = _voxels[x     * _numX * _numY + (y+1) * _numZ + z    ];
				cell.val[4] = _voxels[x     * _numX * _numY + y     * _numZ + (z+1)];
				cell.val[5] = _voxels[(x+1) * _numX * _numY + y     * _numZ + (z+1)];
				cell.val[6] = _voxels[(x+1) * _numX * _numY + (y+1) * _numZ + (z+1)];
				cell.val[7] = _voxels[x     * _numX * _numY + (y+1) * _numZ + (z+1)];

				int numNewTriangles = Polygonise(cell, _isoLevel, &tempTriangles[0]);
				for(unsigned int j = 0; j < numNewTriangles; j++) {
					TRIANGLE triangle = tempTriangles[j];

					glm::vec3 normal = glm::normalize(
						glm::cross(
							triangle.p[1] - triangle.p[0],
					   		triangle.p[2] - triangle.p[0]
						)
					);

					_vertices[vertexIndex+0] = triangle.p[0].x; //P
					_vertices[vertexIndex+1] = triangle.p[0].y; //P
					_vertices[vertexIndex+2] = triangle.p[0].z; //P
					_vertices[vertexIndex+3] = normal.x; //N
					_vertices[vertexIndex+4] = normal.y; //N
					_vertices[vertexIndex+5] = normal.z; //N

					_vertices[vertexIndex+6] = triangle.p[1].x; //P
					_vertices[vertexIndex+7] = triangle.p[1].y; //P
					_vertices[vertexIndex+8] = triangle.p[1].z; //P
					_vertices[vertexIndex+9] = normal.x; //N
					_vertices[vertexIndex+10] = normal.y; //N
					_vertices[vertexIndex+11] = normal.z; //N

					_vertices[vertexIndex+12] = triangle.p[2].x; //P
					_vertices[vertexIndex+13] = triangle.p[2].y; //P
					_vertices[vertexIndex+14] = triangle.p[2].z; //P
					_vertices[vertexIndex+15] = normal.x; //N
					_vertices[vertexIndex+16] = normal.y; //N
					_vertices[vertexIndex+17] = normal.z; //N

					vertexIndex += 18;
				}

				totalTriangles += numNewTriangles;
			}
		}
	}

	_vertices.resize(totalTriangles*18);

	_mesh->uploadVertexData(_vertices);

	_generatedMesh = true;

	return true;
}
void mg::World::reset() {
	_generatedVoxels = false;
	_generatedMesh = false;
}

bool mg::World::setVoxel(unsigned int index, float density) {
	if(_voxels.empty()) {
		printf("failed to modify voxel %u, because there are no \
			voxels in that chunk.n", index);
		return false;
	}

	if(index > _numVoxels) {
		printf("tried to edit out of bounds voxel %u\n", index);
		return false;
	}

	_voxels[index] = density;

	_generatedVoxels = true;

	return true;
}
unsigned int mg::World::getIndex(const glm::vec3& p) const {
	if(_voxelSize == 0.f) {
		printf("tried to get index from position @ %fx%fx%f, but voxel size is zero.\n", p.x, p.y, p.z);
		return 0;
	}

	unsigned int x = p.x / _voxelSize;
	unsigned int y = p.y / _voxelSize;
	unsigned int z = p.z / _voxelSize;

	return (x * _numX * _numY) + (y * _numZ) + z;
}
bool mg::World::setSphere(const glm::vec3& p, unsigned int radius, float density) {
	setVoxel(getIndex(p), density);

	return true;
}

float mg::World::_calcDensity(const glm::vec3& p) const {
	return glm::simplex(p);
}

std::shared_ptr<mg::Mesh> mg::World::getMesh() const {
	return _mesh;
}
