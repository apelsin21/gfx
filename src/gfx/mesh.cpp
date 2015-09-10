#include "gfx/mesh.hpp"

mg::Mesh::Mesh() {
	_format = mg::VertexFormat::PPP;
	_vboSize = 0;
	_iboSize = 0;
	_numFloats = 0;
	_numInts = 0;

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
}
mg::Mesh::~Mesh() {
	if(glIsBuffer(_vbo) == GL_TRUE) {
		glDeleteBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if(glIsBuffer(_ibo) == GL_TRUE) {
		glDeleteBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void mg::Mesh::setVertexFormat(mg::VertexFormat format) {
	_format = format;
}
mg::VertexFormat mg::Mesh::getVertexFormat() const {
	return _format;
}

bool mg::Mesh::uploadVertexData(const std::vector<float>& vertexData) {
	if(vertexData.empty()) {
		printf("tried to upload empty vertex data.\n");
		return false;
	}

	_numFloats = vertexData.size();
	_vboSize = _numFloats * sizeof(float);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		_vboSize,
		&vertexData[0],
		GL_STATIC_DRAW
	);

	return true;
}
bool mg::Mesh::uploadIndexData(const std::vector<int>& indexData) {
	if(indexData.empty()) {
		printf("tried to upload empty vertex data.\n");
		return false;
	}

	_numInts = indexData.size();
	_iboSize = _numInts * sizeof(int);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		_iboSize,
		&indexData[0],
		GL_STATIC_DRAW
	);

	return true;
}

GLuint mg::Mesh::getVertexBuffer() const {
	return _vbo;
}
GLuint mg::Mesh::getIndexBuffer() const {
	return _ibo;
}

unsigned int mg::Mesh::getVertexBufferSize() const {
	return _vboSize;
}
unsigned int mg::Mesh::getIndexBufferSize() const {
	return _iboSize;
}
unsigned int mg::Mesh::getNumFloats() const {
	return _numFloats;
}
unsigned int mg::Mesh::getNumInts() const {
	return _numInts;
}
