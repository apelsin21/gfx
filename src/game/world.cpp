#include "game/world.hpp"

mg::World::World() {
}
mg::World::~World() {
}

bool mg::World::generate() {
	std::srand(std::time(NULL));
	static const int axisSize = 8;
	std::vector<GRIDCELL> cells(axisSize*axisSize*axisSize);

	for(unsigned int x = 0; x < axisSize; x++) {
		for(unsigned int y = 0; y < axisSize; y++) {
			for(unsigned int z = 0; z < axisSize; z++) {

				unsigned int index = x * axisSize * axisSize + y * axisSize + z;

				cells[index].p[0] = glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f); //Bottom back left
				cells[index].p[1] = glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f); //Bottom back right
				cells[index].p[2] = glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f); //Bottom front left
				cells[index].p[3] = glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f); //Bottom front right
				cells[index].p[4] = glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f); //Top back left
				cells[index].p[5] = glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f); //Top back right
				cells[index].p[6] = glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f); //Top front left
				cells[index].p[7] = glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f); //Top front right

				cells[index].val[0] = cells[index].p[0].x;
				cells[index].val[1] = cells[index].p[1].y;
				cells[index].val[2] = cells[index].p[2].z;
				cells[index].val[3] = cells[index].p[3].x;
				cells[index].val[4] = cells[index].p[4].y;
				cells[index].val[5] = cells[index].p[5].z;
				cells[index].val[6] = cells[index].p[6].x;
				cells[index].val[7] = cells[index].p[7].y;
			}                                          
		}
	}

	printf("simplex for 1, 1, 1: %f\n", _calcDensity(glm::vec3(1.0f, 1.0f, 1.0f)));

	std::vector<TRIANGLE> triangles(5);
	int totalFacets = 0;
	int skippedCells = 0;

	for(unsigned int i = 0; i < cells.size(); i++) {
		int newFacets = Polygonise(cells[i], _calcDensity(cells[i].p[0]), &triangles[0]);

		if(newFacets == 0) {
			skippedCells += 1;
			continue;
		}

		totalFacets += newFacets;

		for(unsigned int i = 0; i < newFacets; i += 8) {
			_vertices.emplace_back(triangles[i].p[0].x);
			_vertices.emplace_back(triangles[i].p[0].y);
			_vertices.emplace_back(triangles[i].p[0].z);

			_vertices.emplace_back(triangles[i].p[1].x);
			_vertices.emplace_back(triangles[i].p[1].y);
			_vertices.emplace_back(triangles[i].p[1].z);

			_vertices.emplace_back(triangles[i].p[2].x);
			_vertices.emplace_back(triangles[i].p[2].y);
			_vertices.emplace_back(triangles[i].p[2].z);
		}
	}

	printf("%i gridcells were untouched by the isosurface, and skipped.\n", skippedCells);

	if(totalFacets <= 0) {
		printf("Generated <= 0 facets.\n");
		return false;
	} else {
		unsigned int size = sizeof(float)*(totalFacets*9);
		printf("generated %i triangular facets, for a size of %i B, %f KB, %f MB.\n",
			   	totalFacets, size, size/1024.f, size/1024.f/1024.f);
	}

	printf("World generated %i vertices.\n", _vertices.size());

	if(!_buffer.allocate(_vertices.size(), true, mg::VertexFormat::PPP)) {
		printf("failed to allocate buffer\n");
		return false;
	}

	if(!_buffer.update(_vertices)) {
		printf("failed to update buffer.\n");
		return false;
	}

	return true;
}

float mg::World::_calcDensity(const glm::vec3& pos) const {
	return glm::simplex(pos);
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}
