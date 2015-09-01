#include "game/world.hpp"

mg::World::World() {
	_generatedVoxels = false;
	_generatedVertices = false;

	_isoLevel = 0;
	_numX = 64;
	_numY = 64;
	_numZ = 64;
	_numVoxels = _numX*_numY*_numZ;
	_voxelSize = 0.1f;
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
				float density = _calcDensity(glm::vec3(x*_voxelSize, y*_voxelSize, z*_voxelSize));

				_voxels[x * _numX * _numY + y * _numZ + z] = density;
			}
		}
	}

	_generatedVoxels = true;

	return true;
}
bool mg::World::generateVertices() {
	if(!_generatedVoxels) {
		printf("world tried to generate vertices from no voxels.\n");
		return false;
	}
	if(_voxels.empty()) {
		printf("world can't generate vertices from no voxels.\n");
		return false;
	}

	static const unsigned int numPossibleTriangles = _voxels.size()*5;
	std::vector<TRIANGLE> triangles(numPossibleTriangles);
	std::vector<glm::vec3> normals(numPossibleTriangles);

	unsigned int totalTriangles = 0;
	std::array<TRIANGLE, 5> tempTriangles;
	GRIDCELL cell;

	for(unsigned int x = 0; x < _numX; x++) {
		for(unsigned int y = 0; y < _numY; y++) {
			for(unsigned int z = 0; z < _numZ; z++) {

				unsigned int index = x * _numX * _numY + y * _numZ + z;
				glm::vec3 p = glm::vec3(x * _voxelSize, y * _voxelSize, z * _voxelSize);

				cell.p[0] = p + glm::vec3(0.0	, 0.0f  , 0.0f  );
				cell.p[1] = p + glm::vec3(_voxelSize, 0.0f  , 0.0f  );
				cell.p[2] = p + glm::vec3(_voxelSize, _voxelSize, 0.0f  );
				cell.p[3] = p + glm::vec3(0.0f	, _voxelSize, 0.0f  );
				cell.p[4] = p + glm::vec3(0.0f	, 0.0f  , _voxelSize);
				cell.p[5] = p + glm::vec3(_voxelSize, 0.0f  , _voxelSize);
				cell.p[6] = p + glm::vec3(_voxelSize, _voxelSize, _voxelSize);
				cell.p[7] = p + glm::vec3(0.0f	, _voxelSize, _voxelSize);

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
					int index = totalTriangles + j;
					triangles[index] = tempTriangles[j];

					normals[index] = glm::normalize(
						glm::cross(
							triangles[index].p[1] - triangles[index].p[0],
					   		triangles[index].p[2] - triangles[index].p[0]
						)
					);
				}

				totalTriangles += numNewTriangles;
			}
		}
	}

	triangles.shrink_to_fit();
	normals.shrink_to_fit();

	unsigned int numFloats = triangles.size()*18;
	_vertices = std::vector<float>(numFloats);

	glm::vec3 tempNormal, tempSum;

	for(unsigned int i = 0; i < triangles.size(); i++) {
		for(unsigned int j = 0; j < 3; j++) {
			unsigned int numMaxNeighbours = 2;
			unsigned int numActualNeighbours = 0;
			unsigned int start = i - (numMaxNeighbours/2), end = i + (numMaxNeighbours/2);

			if(end > triangles.size()) {
				end = triangles.size();
			}

			tempSum = glm::vec3(0.f);

			for(unsigned int l = start; l < end; l++) {
				bool sharesVertex = false;
				for(unsigned int m = 0; m < 3; m++) {
					if(triangles[i].p[j] == triangles[l].p[m]) {
						sharesVertex = true;
						break;
					}
				}

				if(sharesVertex) {
					tempSum += normals[l];
					numActualNeighbours++;
				}
			}

			tempNormal = glm::normalize(
				glm::vec3(
					tempSum.x / numActualNeighbours,
				   	tempSum.y / numActualNeighbours,
				   	tempSum.z / numActualNeighbours
				)
			);

			int index = i*18 + j*6;
			_vertices[index+0] = triangles[i].p[j].x;
			_vertices[index+1] = triangles[i].p[j].y;
			_vertices[index+2] = triangles[i].p[j].z;
			_vertices[index+3] = tempNormal.x;
			_vertices[index+4] = tempNormal.y;
			_vertices[index+5] = tempNormal.z;
		}
	}

	if(!_buffer.update(_vertices, true, mg::VertexFormat::PPPNNN)) {
		return false;
	}

	_generatedVertices = true;

	return true;
}
void mg::World::reset() {
	this->_voxels.clear();

	_generatedVoxels = false;
	_generatedVertices = false;
}

bool mg::World::setVoxel(unsigned int index, float density) {
	if(_voxels.empty()) {
		printf("failed to modify voxel %u, because there are no \
			voxels in that chunk.\n", index);
		return false;
	}

	printf("index: %i\n", index);

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
		printf("tried to get index from position \
				@ %fx%fx%f, but voxel size is zero.\n", p.x, p.y, p.z);
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
	if(p.x == 0.f || p.x >= _numX) {
		return 0.f;
	}
	if(p.y == 0.f || p.y >= _numY) {
		return 0.f;
	}
	if(p.z == 0.f || p.z >= _numZ) {
		return 0.f;
	}

	return -p.y;
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}
