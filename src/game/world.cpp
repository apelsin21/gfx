#include "game/world.hpp"

mg::World::World() {
}
mg::World::~World() {
}

bool mg::World::generate() {
	if(!_vertices.empty()) {
		_vertices.clear();
		_buffer.clear();
	}

	std::srand(std::time(NULL));

	int totalTriangles = 0;
	float chunkSize = 32.f;
	GRIDCELL tempVoxel;
	float step = 1.0f;

	for(float x = 0; x <= chunkSize; x += step) {
		for(float y = 0; y <= chunkSize; y += step) {
			for(float z =0; z <= chunkSize; z += step) {
				tempVoxel.p[0] = glm::vec3(x     , y     , z     ); // bottom front left
				tempVoxel.p[1] = glm::vec3(x+step, y     , z     ); // bottom front right
				tempVoxel.p[2] = glm::vec3(x+step, y+step, z     ); // bottom back right
				tempVoxel.p[3] = glm::vec3(x     , y+step, z     ); // bottom back left
				tempVoxel.p[4] = glm::vec3(x     , y     , z+step); // top front left
				tempVoxel.p[5] = glm::vec3(x+step, y     , z+step); // top font right
				tempVoxel.p[6] = glm::vec3(x+step, y+step, z+step); // top back right
				tempVoxel.p[7] = glm::vec3(x     , y+step, z+step); // top back left 
				
				tempVoxel.val[0] = _calcDensity(tempVoxel.p[0]); // bottom front left
				tempVoxel.val[1] = _calcDensity(tempVoxel.p[1]); // bottom front right
				tempVoxel.val[2] = _calcDensity(tempVoxel.p[2]); // bottom back right
				tempVoxel.val[3] = _calcDensity(tempVoxel.p[3]); // bottom back left
				tempVoxel.val[4] = _calcDensity(tempVoxel.p[4]); // top front left
				tempVoxel.val[5] = _calcDensity(tempVoxel.p[5]); // top font right
				tempVoxel.val[6] = _calcDensity(tempVoxel.p[6]); // top back right
				tempVoxel.val[7] = _calcDensity(tempVoxel.p[7]); // top back left 

				std::vector<float> newFloats = polygonize(tempVoxel, 0.0f);
				totalTriangles += newFloats.size() / 3;

				for(unsigned int i = 0; i < newFloats.size(); i++) {
					_vertices.emplace_back(newFloats[i]);
				}
			}
		}
	}

	if(totalTriangles <= 0) {
		printf("Generated <= 0 triangles.\n");
		return false;
	} else {
		unsigned int size = sizeof(float)*(totalTriangles*9);
		printf("generated %i triangles, for a size of %i B, %f KB, %f MB.\n",
			   	totalTriangles, size, size/1024.f, size/1024.f/1024.f);
	}

	if(!_buffer.allocate(_vertices.size(), true, mg::VertexFormat::PPP)) {
		unsigned int size = sizeof(float)*(totalTriangles*9);
		printf("failed to allocate buffer of size: \n", size);
		return false;
	}

	if(!_buffer.update(_vertices)) {
		printf("failed to update world buffer!\n");
		return false;
	}

	return true;
}

float mg::World::_calcDensity(const glm::vec3& p) const {
	float rad = -8.f;

	return rad - glm::length2(p - glm::vec3(0, -rad, 0));
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}

std::vector<float> mg::World::polygonize(GRIDCELL cell, double isoLevel) {
	std::vector<TRIANGLE> triangles(5);
	int numTriangles = Polygonise(cell, isoLevel, &triangles[0]);

	int numFloats = numTriangles * 9;
	std::vector<float> floats(numFloats);

	for(unsigned int i = 0; i < numTriangles; i++) {
		unsigned int floatIndex = i * 9.0f;

		floats[floatIndex+0] = triangles[i].p[0].x;
		floats[floatIndex+1] = triangles[i].p[0].y;
		floats[floatIndex+2] = triangles[i].p[0].z;

		floats[floatIndex+3] = triangles[i].p[1].x;
		floats[floatIndex+4] = triangles[i].p[1].y;
		floats[floatIndex+5] = triangles[i].p[1].z;

		floats[floatIndex+6] = triangles[i].p[2].x;
		floats[floatIndex+7] = triangles[i].p[2].y;
		floats[floatIndex+8] = triangles[i].p[2].z;
	}
	
	return floats;
}
