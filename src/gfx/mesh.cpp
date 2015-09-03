#include "gfx/mesh.hpp"

mg::Mesh::Mesh() {
	_format = mg::VertexFormat::PPP;

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}
mg::Mesh::~Mesh() {
}

void mg::Mesh::setVertexFormat(mg::VertexFormat format) {
	_format = format;
}
mg::VertexFormat mg::Mesh::getVertexFormat() const {
	return _format;
}

bool mg::Mesh::setData(const std::vector<float>& data) {
	_data = data;

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * _data.size(),
		(GLvoid*)&_data[0],
		GL_STATIC_DRAW
	);

	return true;
}
const std::vector<float>& mg::Mesh::getData() const {
	return _data;
}

unsigned int mg::Mesh::getGLHandle() const {
	return _vbo;
}
