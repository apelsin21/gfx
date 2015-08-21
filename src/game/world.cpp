#include "game/world.hpp"

mg::World::World() {
}
mg::World::~World() {
}

bool mg::World::generate() {
	_vertices  = {
		-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
    	-1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
    	-1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    	 1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
    	-1.0f,-1.0f,-1.0f, 0.0f, 1.0f,
    	-1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    	 1.0f,-1.0f, 1.0f, 0.0f, 0.0f,
    	-1.0f,-1.0f,-1.0f, 0.0f, 1.0f,
    	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    	 1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
    	 1.0f,-1.0f,-1.0f, 0.0f, 1.0f,
    	-1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
    	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    	-1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    	 1.0f,-1.0f, 1.0f, 0.0f, 0.0f,
    	-1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
    	-1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    	-1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
    	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
    	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    	 1.0f,-1.0f,-1.0f, 0.0f, 1.0f,
    	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    	 1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
    	 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
    	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    	 1.0f, 1.0f,-1.0f, 0.0f, 1.0f,
    	-1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    	-1.0f, 1.0f,-1.0f, 0.0f, 1.0f,
    	-1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
	};

	_buffer.allocate(_vertices.size(), true, mg::VertexFormat::PPPTT);
	_buffer.update(_vertices);

	return true;
}

const mg::GLVertexBuffer& mg::World::getBuffer() const {
	return _buffer;
}
std::vector<float> mg::World::getVertices() const {
	return _vertices;
}
