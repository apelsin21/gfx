#include "gfx/gl_vertex_buffer.hpp"

mg::GLVertexBuffer::GLVertexBuffer() {
	_usage = 0;
	_size = 0;
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}
mg::GLVertexBuffer::~GLVertexBuffer() {
	if(glIsBuffer(_vbo) == GL_TRUE) {
		glDeleteBuffers(1, &this->_vbo);
	}
}

void mg::GLVertexBuffer::bind() const {
	if(glIsBuffer(_vbo) != GL_TRUE) {
		printf("Tried to bind invalid GLVertexBuffer.\n");
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
}
void mg::GLVertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool mg::GLVertexBuffer::allocate(std::size_t size, bool is_static) {
	if(size == 0) {
		printf("GLVertexBuffer tried to allocate 0 bytes of memory.\n");
		return false;
	}

	_usage = is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

	this->bind();
	glBufferData(GL_ARRAY_BUFFER, size, NULL, _usage);
	_size = size;
	return true;
}
bool mg::GLVertexBuffer::update(const std::vector<float>& vertices) {
	if(vertices.empty()) {
		printf("GLVertexBuffer tried to upload empty vertex list\n");
	}
	if(vertices.size() > _size) {
		printf("GLVertexBuffer tried to overflow.\n");
		return false;
	}

	this->bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), (GLvoid*)&vertices[0], this->_usage);

	return true;
}
bool mg::GLVertexBuffer::updateRegion(const std::vector<float>& vertices, std::size_t offset, std::size_t size) {
	if(vertices.empty()) {
		printf("GLVertexBuffer tried to upload empty vertex list\n");
	}
	if(sizeof(float) * vertices.size() >  _size) {
		printf("GLVertexBuffer tried to overflow.\n");
		return false;
	}
	if(offset + (sizeof(float) * vertices.size()) > _size) {
		printf("GLVertexBuffer tried to overflow.\n");
		return false;
	}


	this->bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, (GLvoid*)&vertices[0]);

	return true;
}

bool mg::GLVertexBuffer::isStatic() const {
	if(_usage == GL_STATIC_DRAW) {
		return true;
	}

	return false;
}
std::size_t mg::GLVertexBuffer::getSize() const {
	return _size;
}
unsigned int mg::GLVertexBuffer::getGLHandle() const {
	return this->_vbo;
}
