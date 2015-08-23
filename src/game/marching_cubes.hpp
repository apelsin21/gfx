#ifndef MARCHING_CUBES_HPP
#define MARCHING_CUBES_HPP

#include <cmath>
#include <glm/glm.hpp>

struct TRIANGLE {
	glm::vec3 p[3];
};

struct GRIDCELL {
	glm::vec3 p[8];
	double val[8];
};

int Polygonise(GRIDCELL, double, TRIANGLE*);
glm::vec3 VertexInterp(double, const glm::vec3&, const glm::vec3&, double, double);

#endif //MARCHING_CUBES_HPP
