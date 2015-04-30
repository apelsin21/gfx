#include "gfx/vertex.hpp"

gfx::Vertex::Vertex() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->u = 0.0f;
	this->v = 0.0f;
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
	this->a = 0.0f;
}
gfx::Vertex::Vertex(int x, int y, int u, int v, int r, int g, int b, int a) {
	this->x = x;
	this->y = y;
	this->u = u;
	this->v = v;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
gfx::Vertex::~Vertex() {
}
