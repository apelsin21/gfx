#include "gfx/gl_vertex_buffer.hpp"

mg::GLVertexBuffer::GLVertexBuffer(unsigned int max, bool is_static) {
	this->_vertices.reserve(max);
	this->_numVertices = 0;
	this->_maxVertices = max;
	this->_usage = is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
	glGenBuffers(1, &this->_vbo);
}
mg::GLVertexBuffer::~GLVertexBuffer() {
	glDeleteBuffers(1, &this->_vbo);
}

unsigned int mg::GLVertexBuffer::getMaxVertices() const {
	return this->_maxVertices;
}
unsigned int mg::GLVertexBuffer::getGLHandle() const {
	return this->_vbo;
}

void mg::GLVertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
}
void mg::GLVertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool mg::GLVertexBuffer::setVertices(const std::vector<float>& vertices) {
	if(vertices.size() != this->_maxVertices) {
		printf("Error: tried to set vertexbuffer data with wrong size.\n");
		return false;
	}

	this->bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*this->_maxVertices, (GLvoid*)&vertices[0], this->_usage);

	return true;
}

bool mg::GLVertexBuffer::updateVertices(const std::vector<float>& vertices, unsigned int offset) {
	if(vertices.size() > this->_maxVertices) {
		printf("Error: overflow attempted whilst updating data in vertexbuffer.\n");
		return false;
	}

	this->bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float)*vertices.size(), (GLvoid*)&vertices[0]);

	return true;
}

unsigned int mg::GLVertexBuffer::getNumTriangles() const {
	return (unsigned int)this->_numVertices / 3;
}
