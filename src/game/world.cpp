#include "game/world.hpp"

mg::World::World() {
	_generatedVoxels = false;
	_generatedVertices = false;
	_isoLevel = 0.0;
}
mg::World::~World() {
}

bool mg::World::generateVoxels() {
	if(_generatedVoxels) {
		printf("World tried to regenerate voxels!\n");
		return false;
	}

	std::array<std::array<std::array<glm::vec3, _numZ>, _numY>, _numX> positions;
	std::array<std::array<std::array<float, _numZ>, _numY>, _numX> values;
	//glm::vec3[_numX][_numY][_numZ] positions;
	//float[_numX][_numY][_numZ] values;
	unsigned int numTrue = 0;

	//use volexample as example
	//generate "c", a.k.a the value of the density function
	//at the position x, y, z, for the number of voxels you want
	//
	//if it's positive, discard that value, for example.

	for(unsigned int z = 0; z < _numZ; z++) {
		for(unsigned int y = 0; y < _numY; y++) {
			for(unsigned int x = 0; x < _numX; x++) {
				glm::vec3 p(x * _scale, y * _scale, z * _scale);
				float density = _calcDensity(p);

				positions[x][y][z] = p;
				values[x][y][z] = density;
				if(density < 0) {
					numTrue++;
				}
			}
		}
	}

	printf("generated %u, max %u\n", numTrue, _numVoxels);

	//ALMOST
	//if the voxel @ x y z had a positive density value
	//(i.e a value that is not solid)
	//DON'T use it below
	//instead use another value
	//
	//... i think

	for(unsigned int x = 0; x < _numX; x++) {
		for(unsigned int y = 0; y < _numY; y++) {
			for(unsigned int z = 0; z < _numZ; z++) {
				GRIDCELL voxel;

				glm::vec3 p = positions[x][y][z];
				voxel.p[0] = p + glm::vec3(0     , 0.f   , 0.f  ); // bottom front left
				voxel.p[1] = p + glm::vec3(_scale, 0.f   , 0.f  ); // bottom front right
				voxel.p[2] = p + glm::vec3(_scale, _scale, 0.f  ); // bottom back right
				voxel.p[3] = p + glm::vec3(0     , _scale, 0.f  ); // bottom back left
				voxel.p[4] = p + glm::vec3(0     , 0.f   , _scale); // top front left
				voxel.p[5] = p + glm::vec3(_scale, 0.f   , _scale); // top font right
				voxel.p[6] = p + glm::vec3(_scale, _scale, _scale); // top back right
				voxel.p[7] = p + glm::vec3(0     , _scale, _scale); // top back left 
				
				//LOOK AT VOLEXAMPLE LINE 97 to 151
				voxel.val[0] = values[x  ][y  ][z  ]; // bottom front left
				voxel.val[1] = values[x+1][y  ][z  ]; // bottom front right
				voxel.val[2] = values[x+1][y+1][z  ]; // bottom back right
				voxel.val[3] = values[x  ][y+1][z  ]; // bottom back left
				voxel.val[4] = values[x  ][y  ][z+1]; // top front left
				voxel.val[5] = values[x+1][y  ][z+1]; // top font right
				voxel.val[6] = values[x+1][y+1][z+1]; // top back right
				voxel.val[7] = values[x  ][y+1][z+1]; // top back left 

				_voxels.emplace_back(voxel);
			}
		}
	}

	//for(int x = 0; x < _numX; x++) {
	//	for(int y = 0; y < _numY; y++) {
	//		for(int z = 0; z < _numZ; z++) {
	//			pos = glm::vec3(x * scale, y * scale, z * scale);

	//			tempVoxel.p[0] = pos + glm::vec3(0    , 0.f   , 0.f  ); // bottom front left
	//			tempVoxel.p[1] = pos + glm::vec3(scale, 0.f   , 0.f  ); // bottom front right
	//			tempVoxel.p[2] = pos + glm::vec3(scale, scale , 0.f  ); // bottom back right
	//			tempVoxel.p[3] = pos + glm::vec3(0    , scale , 0.f  ); // bottom back left
	//			tempVoxel.p[4] = pos + glm::vec3(0    , 0.f   , scale); // top front left
	//			tempVoxel.p[5] = pos + glm::vec3(scale, 0.f   , scale); // top font right
	//			tempVoxel.p[6] = pos + glm::vec3(scale, scale , scale); // top back right
	//			tempVoxel.p[7] = pos + glm::vec3(0    , scale , scale); // top back left 
	//			
	//			tempVoxel.val[0] = _calcDensity(tempVoxel.p[0]); // bottom front left
	//			tempVoxel.val[1] = _calcDensity(tempVoxel.p[1]); // bottom front right
	//			tempVoxel.val[2] = _calcDensity(tempVoxel.p[2]); // bottom back right
	//			tempVoxel.val[3] = _calcDensity(tempVoxel.p[3]); // bottom back left
	//			tempVoxel.val[4] = _calcDensity(tempVoxel.p[4]); // top front left
	//			tempVoxel.val[5] = _calcDensity(tempVoxel.p[5]); // top font right
	//			tempVoxel.val[6] = _calcDensity(tempVoxel.p[6]); // top back right
	//			tempVoxel.val[7] = _calcDensity(tempVoxel.p[7]); // top back left 

	//			_voxels[x * _numX * _numY + y * _numZ + z] = tempVoxel;
	//		}
	//	}
	//}
	
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
	std::array<TRIANGLE, 5> tempTriangles; // is overwritten

	// iterate through all voxels
	for(unsigned int i = 0; i < _voxels.size(); i++) {
		int numNewTriangles = Polygonise(_voxels[i], _isoLevel, &tempTriangles[0]);

		// iterate through all new triangles for the voxel
		// and add them and their normals to their respective lists
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

	if(triangles.size() != normals.size()) {
		printf("World generated number of triangles(%u) and normals(%u) isn't the same.\n",
			   	triangles.size(), normals.size());
		return false;
	}

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

	unsigned int size = sizeof(float)*numFloats;
	float maxPossibleSize = _voxels.size() * 5 * 27 * 4 / 1024.f / 1024.f;
	printf("%i voxels generated %i triangles, for a size of %u B, %f KB, %f MB.\n", _voxels.size(),
		   	totalTriangles, size, size/1024.f, size/1024.f/1024.f);

	printf("max possible size: %f MB.\n", maxPossibleSize);

	if(!_buffer.update(_vertices, true, mg::VertexFormat::PPPNNN)) {
		printf("failed to allocate vertex buffer of %u bytes.\n", size);
		return false;
	}

	_generatedVertices = true;

	return true;
}

float mg::World::_calcDensity(const glm::vec3& p) const {
	glm::vec3 origin((_numX*_scale) / 2.0f, (_numY*_scale) / 2.0f, (_numZ*_scale) / 2.0f);

	return glm::length(p - origin) - ((_numX*0.1f)/2.0f);
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}
