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

	// create an array to hold all voxels
	_voxels = std::unique_ptr<GRIDCELL[]>(new GRIDCELL[_numVoxels]);
	GRIDCELL tempVoxel; // is overwritten

	float width = 0.1f;

	for(int i = 0; i < _numX; i++) {
		for(int j = 0; j < _numY; j++) {
			for(int k = 0; k < _numZ; k++) {
				// we want the distance between the voxels
				// to be the same as their width
				float x = i * width, y = j * width, z = k * width;

				tempVoxel.p[0] = glm::vec3(x      , y      , z      ); // bottom front left
				tempVoxel.p[1] = glm::vec3(x+width, y      , z      ); // bottom front right
				tempVoxel.p[2] = glm::vec3(x+width, y+width, z      ); // bottom back right
				tempVoxel.p[3] = glm::vec3(x      , y+width, z      ); // bottom back left
				tempVoxel.p[4] = glm::vec3(x      , y      , z+width); // top front left
				tempVoxel.p[5] = glm::vec3(x+width, y      , z+width); // top font right
				tempVoxel.p[6] = glm::vec3(x+width, y+width, z+width); // top back right
				tempVoxel.p[7] = glm::vec3(x      , y+width, z+width); // top back left 
				
				tempVoxel.val[0] = _calcDensity(tempVoxel.p[0]); // bottom front left
				tempVoxel.val[1] = _calcDensity(tempVoxel.p[1]); // bottom front right
				tempVoxel.val[2] = _calcDensity(tempVoxel.p[2]); // bottom back right
				tempVoxel.val[3] = _calcDensity(tempVoxel.p[3]); // bottom back left
				tempVoxel.val[4] = _calcDensity(tempVoxel.p[4]); // top front left
				tempVoxel.val[5] = _calcDensity(tempVoxel.p[5]); // top font right
				tempVoxel.val[6] = _calcDensity(tempVoxel.p[6]); // top back right
				tempVoxel.val[7] = _calcDensity(tempVoxel.p[7]); // top back left 

				_voxels[i * _numX * _numY + j * _numZ + k] = tempVoxel;
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

	static const unsigned int numPossibleTriangles = _numX*_numY*_numZ*5;
	std::vector<TRIANGLE> triangles(numPossibleTriangles);
	std::vector<glm::vec3> normals(numPossibleTriangles);

	unsigned int totalTriangles = 0;
	std::array<TRIANGLE, 5> tempTriangles; // is overwritten

	// iterate through all voxels
	for(unsigned int i = 0; i < _numVoxels; i++) {
		int numNewTriangles = Polygonise(_voxels[i], 0.0, &tempTriangles[0]);

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
	float maxPossibleSize = _numVoxels * 5 * 27 * 4 / 1024.f / 1024.f;
	printf("%i voxels generated %i triangles, for a size of %u B, %f KB, %f MB.\n", _numVoxels,
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
	return glm::simplex(p);
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}
