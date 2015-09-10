#include "gfx/renderer.hpp"

mg::Renderer::Renderer() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}
mg::Renderer::~Renderer() {
	if(glIsVertexArray(_vao) == GL_TRUE) {
		glDeleteVertexArrays(1, &_vao);
	}
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


bool mg::Renderer::render(std::shared_ptr<mg::FrameBuffer> fbo, std::shared_ptr<mg::Batch> batch) {
	if(batch == nullptr) {
		printf("renderer tried to render uninstanced batch.\n");
		return false;
	}

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if(fbo->isComplete()) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo->getGLHandle());
		glBindTexture(GL_TEXTURE_2D, batch->getTexture()->getGLHandle());
		glBindVertexArray(batch->getVAO());
	} else {
		printf("renderer tried to render to incomplete FBO.\n");
		return false;
	}

	glm::vec2 res(fbo->getColorTexture()->getResolution());

	glViewport(
		0,
		0,
		res.x,
		res.y
	);

	glClearColor(0.f, 1.f, 1.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(glIsProgram(batch->getShader()->getGLHandle()) == GL_FALSE) {
		printf("renderer batch got invalid shaderprogram.\n");
		return false;
	}

	const GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, buffers);

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
	} else {
		printf("shader uniforms are nullptr.\n");
		return false;
	}
	
	glBindTexture(GL_TEXTURE_2D, batch->getTexture()->getGLHandle());
	glDrawArrays(GL_TRIANGLES, 0, batch->getMesh()->getNumFloats() / 6);

	return true;
}
bool mg::Renderer::render(std::shared_ptr<mg::Batch> batch) {
	if(batch == nullptr) {
		printf("renderer tried to render uninstanced batch.\n");
		return false;
	}
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, batch->getTexture()->getGLHandle());
	glBindVertexArray(batch->getVAO());

	glViewport(0, 0, _res.x, _res.y);

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(batch->getShader()->getGLHandle());

	glDrawArrays(GL_TRIANGLES, 0, batch->getMesh()->getNumFloats() / 4);

	return true;
}
