#include "modern_gl_renderer.hpp"

mg::ModernGLRenderer::ModernGLRenderer() {
}
mg::ModernGLRenderer::~ModernGLRenderer() {
}

void mg::ModernGLRenderer::drawBuffer(mg::GLVertexBuffer& buffer) {
	glBindVertexArray(this->_vao);
	buffer.bind();
	glDrawArrays(GL_TRIANGLES, 0, buffer.getNumTriangles());
}
