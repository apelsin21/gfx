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

	unsigned int totalTriangles = 0;
	static const int numX = 2, numY = 8, numZ = 2;
	GRIDCELL tempVoxel;
	std::vector<TRIANGLE> triangles((numX*numY*numZ)*5);
	std::vector<glm::vec3> normals((numX*numY*numZ)*5);
	float step = 0.1f;

	for(float x = 0; x <= numX; x += step) {
		for(float y = 0; y <= numY; y += step) {
			for(float z = 0; z <= numZ; z += step) {
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

				std::vector<TRIANGLE> tempTriangles(5);
				int newTriangles = Polygonise(tempVoxel, 0.0, &tempTriangles[0]);
				totalTriangles += newTriangles;

				for(unsigned int i = 0; i < newTriangles; i++) {
					triangles.emplace_back(tempTriangles[i]);
					normals.emplace_back(glm::normalize(glm::cross(tempTriangles[i].p[1] - tempTriangles[i].p[0], tempTriangles[i].p[2] - tempTriangles[i].p[0])));
				}
			}
		}
	}

	triangles.shrink_to_fit();
	normals.shrink_to_fit();

	for(unsigned int i = 0; i < triangles.size(); i++) {
		for(unsigned int j = 0; j < 3; j++) {
			_vertices.emplace_back(triangles[i].p[j].x);
			_vertices.emplace_back(triangles[i].p[j].y);
			_vertices.emplace_back(triangles[i].p[j].z);

			unsigned int numNeighbours = 24;
			unsigned int start = i - (numNeighbours/2), end = i + (numNeighbours/2);

			if(end > triangles.size()) {
				end = triangles.size();
			}

			glm::vec3 sum;

			for(unsigned int l = start; l < end; l++) {
				bool sharesVertex = false;
				for(unsigned int m = 0; m < 3; m++) {
					if(triangles[l].p[m] == triangles[i].p[j]) {
						sharesVertex = true;
						break;
					}
				}

				if(sharesVertex) {
					sum += normals[l];
				}
			}

			glm::vec3 normal = glm::normalize(glm::vec3(sum.x / numNeighbours, sum.y / numNeighbours, sum.z / numNeighbours));

			_vertices.emplace_back(normal.x);
			_vertices.emplace_back(normal.y);
			_vertices.emplace_back(normal.z);
		}
	}

	if(totalTriangles == 0) {
		printf("Generated 0 triangles.\n");
		return false;
	}


	unsigned int size = sizeof(float)*_vertices.size();
	printf("generated %i triangles, for a size of %u B, %f KB, %f MB.\n",
		   	totalTriangles, size, size/1024.f, size/1024.f/1024.f);

	if(!_buffer.allocate(_vertices.size(), true, mg::VertexFormat::PPPNNN)) {
		printf("failed to allocate buffer of %u bytes.\n", size);
		return false;
	}

	if(!_buffer.update(_vertices)) {
		printf("failed to update world buffer!\n");
		return false;
	}

	return true;
}

float mg::World::_calcDensity(const glm::vec3& p) const {
	return glm::simplex(p);
}
glm::vec3 mg::World::_calcNormal(const glm::vec3& p) const {
	// wrong, doesn't work, etc.
	const float H = 0.001f;
	const float dx = _calcDensity(p + glm::vec3(H, 0.f, 0.f)) - _calcDensity(p - glm::vec3(H, 0.f, 0.f));
	const float dy = _calcDensity(p + glm::vec3(0.f, H, 0.f)) - _calcDensity(p - glm::vec3(0.f, H, 0.f));
	const float dz = _calcDensity(p + glm::vec3(0.f, 0.f, H)) - _calcDensity(p - glm::vec3(0.f, 0.f, H));
	
	return glm::normalize(glm::vec3(dx, dy, dz));
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}
