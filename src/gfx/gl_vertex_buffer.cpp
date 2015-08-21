#include "gfx/gl_vertex_buffer.hpp"

mg::GLVertexBuffer::GLVertexBuffer() {
	_usage = 0;
	_maxVertices = 0;
	_numVertices = 0;
	_format = mg::VertexFormat::P;

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

bool mg::GLVertexBuffer::allocate(unsigned int max, bool is_static, mg::VertexFormat format) {
	if(max == 0) {
		printf("GLVertexBuffer tried to allocate 0 vertices.\n");
		return false;
	}
	if(_maxVertices != 0) {
		printf("GLVertexBuffer tried to reallocate memory.\n");
		return false;
	}

	_usage = is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
	_format = format;

	this->bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * max, NULL, _usage);
	_maxVertices = max;
	return true;
}
bool mg::GLVertexBuffer::update(const std::vector<float>& vertices) {
	if(vertices.empty()) {
		printf("GLVertexBuffer tried to upload empty vertex list\n");
		return 0;
	}
	if(vertices.size() != _maxVertices) {
		printf("GLVertexBuffer tried to update buffer with wrong size.\n");
		return false;
	}

	this->bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), (GLvoid*)&vertices[0], this->_usage);
	_numVertices = vertices.size();
	_maxVertices = vertices.size();

	return true;
}
bool mg::GLVertexBuffer::updateRegion(const std::vector<float>& vertices, unsigned int offset, unsigned int numVertices) {
	if(vertices.empty()) {
		printf("GLVertexBuffer tried to upload empty vertex list\n");
		return false;
	}
	if(vertices.size() >  _maxVertices) {
		printf("GLVertexBuffer tried to overflow.\n");
		return false;
	}
	if(offset + vertices.size() > _maxVertices) {
		printf("GLVertexBuffer tried to overflow.\n");
		return false;
	}

	this->bind();
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * offset, sizeof(float) * numVertices, (GLvoid*)&vertices[0]);

	if(_numVertices != _maxVertices) {
		if(offset >= 0 && offset <= _numVertices) {
			if(offset + numVertices > _numVertices) {
				_numVertices += offset + numVertices - (_numVertices);
			}
		} else {
			_numVertices += numVertices;
		}
	}

	return true;
}

bool mg::GLVertexBuffer::isStatic() const {
	if(_usage == GL_STATIC_DRAW) {
		return true;
	}

	return false;
}
unsigned int mg::GLVertexBuffer::getNumVertices() const {
	return _numVertices;
}
unsigned int mg::GLVertexBuffer::getMaxVertices() const {
	return _maxVertices;
}
unsigned int mg::GLVertexBuffer::getGLHandle() const {
	return this->_vbo;
}
mg::VertexFormat mg::GLVertexBuffer::getFormat() const {
	return _format;
}
