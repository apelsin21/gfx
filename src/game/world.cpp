#include "game/world.hpp"

mg::World::World() {
	_generatedVoxels = false;
	_generatedVertices = false;
}
mg::World::~World() {
}

bool mg::World::generateVoxels() {
	if(_generatedVoxels) {
		printf("World tried to regenerate voxels!\n");
		return false;
	}

	//std::array<std::array<std::array<glm::vec3, _numZ>, _numY>, _numX> positions;
	//std::array<std::array<std::array<float, _numZ>, _numY>, _numX> values;

	_voxels = std::vector<GRIDCELL>(_numVoxels);
	std::vector<float> values(_numVoxels);

	for(unsigned int x = 0; x < _numX; x++) {
		for(unsigned int y = 0; y < _numY; y++) {
			for(unsigned int z = 0; z < _numZ; z++) {
				float density = _calcDensity(glm::vec3(x*_scale, y*_scale, z*_scale));
				values[x * _numX * _numY + y * _numZ + z] = density;
			}
		}
	}

	GRIDCELL voxel;

	for(unsigned int x = 0; x < _numX; x++) {
		for(unsigned int y = 0; y < _numY; y++) {
			for(unsigned int z = 0; z < _numZ; z++) {

				glm::vec3 p = glm::vec3(x * _scale, y * _scale, z * _scale);

				voxel.p[0] = p + glm::vec3(0.0f  , 0.0f  , 0.0f  );
				voxel.p[1] = p + glm::vec3(_scale, 0.0f  , 0.0f  );
				voxel.p[2] = p + glm::vec3(_scale, _scale, 0.0f  );
				voxel.p[3] = p + glm::vec3(0.0f  , _scale, 0.0f  );
				voxel.p[4] = p + glm::vec3(0.0f  , 0.0f  , _scale);
				voxel.p[5] = p + glm::vec3(_scale, 0.0f  , _scale);
				voxel.p[6] = p + glm::vec3(_scale, _scale, _scale);
				voxel.p[7] = p + glm::vec3(0.0f  , _scale, _scale);

				voxel.val[0] = values[x   * _numX * _numY + y   * _numZ + z  ];
				voxel.val[1] = values[x+1 * _numX * _numY + y   * _numZ + z  ];
				voxel.val[2] = values[x+1 * _numX * _numY + y+1 * _numZ + z  ];
				voxel.val[3] = values[x   * _numX * _numY + y+1 * _numZ + z  ];
				voxel.val[4] = values[x   * _numX * _numY + y   * _numZ + z+1];
				voxel.val[5] = values[x+1 * _numX * _numY + y   * _numZ + z+1];
				voxel.val[6] = values[x+1 * _numX * _numY + y+1 * _numZ + z+1];
				voxel.val[7] = values[x   * _numX * _numY + y+1 * _numZ + z+1];
				
				_voxels[x * _numX * _numY + y * _numZ + z] = voxel;
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
	if(_generatedVertices) {
		printf("world tried to regenerate vertices from voxels.\n");
		return false;
	}

	static const unsigned int numPossibleTriangles = _voxels.size()*5;
	std::vector<TRIANGLE> triangles(numPossibleTriangles);
	std::vector<glm::vec3> normals(numPossibleTriangles);

	unsigned int totalTriangles = 0;
	std::array<TRIANGLE, 5> tempTriangles;

	for(unsigned int i = 0; i < _voxels.size(); i++) {
		int numNewTriangles = Polygonise(_voxels[i], _isoLevel, &tempTriangles[0]);

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

			int index = (i*18) + (j*6);
			_vertices[index+0] = triangles[i].p[j].x;
			_vertices[index+1] = triangles[i].p[j].y;
			_vertices[index+2] = triangles[i].p[j].z;
			_vertices[index+3] = tempNormal.x;
			_vertices[index+4] = tempNormal.y;
			_vertices[index+5] = tempNormal.z;
		}
	}

	if(totalTriangles == 0) {
		printf("Generated 0 triangles.\n");
		return false;
	}

	if(!_buffer.update(_vertices, true, mg::VertexFormat::PPPNNN)) {
		return false;
	}

	_generatedVertices = true;

	return true;
}

float mg::World::_calcDensity(const glm::vec3& p) const {
	//glm::vec3 origin((_numX*_scale) / 2.0f, (_numY*_scale) / 2.0f, (_numZ*_scale) / 2.0f);

	//return glm::length(p - origin) - ((_numX*0.1f)/2.0f);
	
	return glm::simplex(p);
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}
