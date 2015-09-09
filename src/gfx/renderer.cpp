#include "gfx/renderer.hpp"

mg::Renderer::Renderer() {
}
mg::Renderer::~Renderer() {
}

void mg::Renderer::setClearColor(const glm::vec4& color) {
	_clearColor = color;

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
}
glm::vec4 mg::Renderer::getClearColor() const {
	return _clearColor;
}

void mg::Renderer::setSize(const glm::vec2& res) {
	_res = res;
	glViewport(0, 0, _res.x, _res.y);
}
glm::vec2 mg::Renderer::getSize() const {
	return _res;
}


bool mg::Renderer::render(mg::FrameBuffer& fbo, const std::shared_ptr<mg::Batch>& batch) {
	if(batch == nullptr) {
		printf("renderer tried to render uninstanced batch.\n");
		return false;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if(fbo.isComplete()) {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo.getGLHandle());
	} else {
		printf("renderer tried to render to incomplete FBO.\n");
		return false;
	}
	
	glViewport(
		0,
		0,
		fbo.getColorTexture()->getResolution().x, 
		fbo.getColorTexture()->getResolution().y
	);

	glClearColor(1.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(batch->getVAO());
	glBindTexture(GL_TEXTURE_2D, batch->getTexture()->getGLHandle());
	glUseProgram(batch->getShader()->getGLHandle());
	
	if(batch->getUniforms() != nullptr) {
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
	}
	
	glDrawArrays(GL_TRIANGLES, 0, batch->getMesh()->getNumFloats() / 6);

	return true;
}
bool mg::Renderer::render(const std::shared_ptr<mg::Batch>& batch) {
	if(batch == nullptr) {
		printf("renderer tried to render uninstanced batch.\n");
		return false;
	}
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glViewport(0, 0, _res.x, _res.y);

	glClearColor(0.f, 1.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(batch->getVAO());
	glBindTexture(GL_TEXTURE_2D, batch->getTexture()->getGLHandle());

	glUseProgram(batch->getShader()->getGLHandle());
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	return true;
}
