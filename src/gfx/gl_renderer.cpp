#include "gfx/gl_renderer.hpp"

mg::GLRenderer::GLRenderer() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
mg::GLRenderer::~GLRenderer() {
	if(glIsVertexArray(_vao) == GL_TRUE) {
		glDeleteVertexArrays(1, &_vao);
	}
}

void mg::GLRenderer::setClearColor(const mg::Color& color) {
	_clearColor = color;

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
}
mg::Color mg::GLRenderer::getClearColor() const {
	return _clearColor;
}

void mg::GLRenderer::setSize(const glm::vec2& res) {
	_res = res;
	glViewport(0, 0, _res.x, _res.y);
}
glm::vec2 mg::GLRenderer::getSize() const {
	return _res;
}

bool mg::GLRenderer::render(const std::shared_ptr<mg::Batch>& batch) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(batch->getShader()->getGLHandle());

	for(const auto &pair : batch->getUniforms()->getFloats()) {
		glUniform1f(
			batch->getShader()->getUniformLocation(pair.first),
			*pair.second.get()
		);
	}
	for(const auto &pair : batch->getUniforms()->getVec2s()) {
		glUniform2f(
			batch->getShader()->getUniformLocation(pair.first),
			pair.second->x,
			pair.second->y
		);
	}
	for(const auto &pair : batch->getUniforms()->getVec3s()) {
		glUniform3f(
			batch->getShader()->getUniformLocation(pair.first),
			pair.second->x,
			pair.second->y,
			pair.second->z
		);
	}
	for(const auto &pair : batch->getUniforms()->getVec4s()) {
		glUniform4f(
			batch->getShader()->getUniformLocation(pair.first),
			pair.second->x,
			pair.second->y,
			pair.second->z,
			pair.second->w
		);
	}
	for(const auto &pair : batch->getUniforms()->getMatrices()) {
		glUniformMatrix4fv(
			batch->getShader()->getUniformLocation(pair.first),
			1,
			GL_FALSE,
			pair.second
		);
	}

	glBindTexture(GL_TEXTURE_2D, batch->getTexture()->getID());

	//GET DATA
	glDrawArrays(GL_TRIANGLES, 0, batch->getMesh()->getData().size() / 5);

	return true;
}
