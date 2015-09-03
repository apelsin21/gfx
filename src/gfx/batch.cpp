#include "gfx/batch.hpp"

mg::Batch::Batch() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}
mg::Batch::~Batch() {
	if(glIsVertexArray(_vao) == GL_TRUE) {
		glDeleteVertexArrays(1, &_vao);
	}
}

bool mg::Batch::set(
		const std::shared_ptr<mg::Mesh>& mesh,
		const std::shared_ptr<mg::ShaderUniforms>& uniforms,
		const std::shared_ptr<mg::GLTexture>& texture,
		const std::shared_ptr<mg::GLShader>& shader) {

	if(mesh == nullptr) {
		printf("tried to set batch mesh to nullptr\n");
		return false;
	}
	if(uniforms == nullptr) {
		printf("tried to set batch uniforms to nullptr\n");
		return false;
	}
	if(texture == nullptr) {
		printf("tried to set batch texture to nullptr\n");
		return false;
	}
	if(shader == nullptr) {
		printf("tried to set batch shader to nullptr\n");
		return false;
	}

	_mesh = mesh;
	_uniforms = uniforms;
	_texture = texture;
	_shader = shader;

	glBindVertexArray(_vao);

	GLint pos = _shader->getAttribLocation("v_pos");
	GLint normal = _shader->getAttribLocation("v_normal");

	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(normal);

	glBindBuffer(GL_ARRAY_BUFFER, _mesh->getGLHandle());

	switch(_mesh->getVertexFormat()) {
	case mg::VertexFormat::PPPNNN:
		glVertexAttribPointer(
				pos,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(float) * 6,
				(GLvoid*)0
		);
		glVertexAttribPointer(
			normal,
			3,
		   	GL_FLOAT,
			GL_FALSE,
			sizeof(float) * 6,
			(GLvoid*)(sizeof(float) * 3)
		);
		break;
	default:
		printf("batch->set() got unhandled vertex format\n");
		return false;
		break;
	}

	return true;
}

std::shared_ptr<mg::Mesh> mg::Batch::getMesh() const {
	return _mesh;
}
std::shared_ptr<mg::ShaderUniforms> mg::Batch::getUniforms() const {
	return _uniforms;
}
std::shared_ptr<mg::GLTexture> mg::Batch::getTexture() const {
	return _texture;
}
std::shared_ptr<mg::GLShader> mg::Batch::getShader() const {
	return _shader;
}
