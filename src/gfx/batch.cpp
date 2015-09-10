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
		std::shared_ptr<mg::Mesh> mesh,
		std::shared_ptr<mg::ShaderUniforms> uniforms,
		std::shared_ptr<mg::Texture> texture,
		std::shared_ptr<mg::Shader> shader) {

	if(mesh == nullptr) {
		printf("tried to set batch mesh to nullptr\n");
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

	if(glIsVertexArray(_vao) == GL_FALSE) {
		printf("batch failed to bind VAO.\n");
		return false;
	}
	if(glIsBuffer(_mesh->getVertexBuffer()) == GL_FALSE) {
		printf("batch failed to bind mesh vertex buffer.\n");
		return false;
	}

	glBindVertexArray(_vao);

	GLint pos = _shader->getAttribLocation("v_pos");
	GLint normal = _shader->getAttribLocation("v_normal");
	GLint uv = _shader->getAttribLocation("v_uv");

	switch(_mesh->getVertexFormat()) {
		case mg::VertexFormat::PPTT:
			if(pos == -1) {
				printf("batch failed to find v_pos shader attribute.\n");
				return false;
			}
			if(uv == -1) {
				printf("batch failed to find v_uv shader attribute.\n");
				return false;
			}
			glEnableVertexAttribArray(pos);
			glEnableVertexAttribArray(uv);

			glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBuffer());

			glVertexAttribPointer(
					pos,
					2,
					GL_FLOAT,
					GL_FALSE,
					sizeof(float) * 4,
					(GLvoid*)0
			);
			glVertexAttribPointer(
				uv,
				2,
			   	GL_FLOAT,
				GL_FALSE,
				sizeof(float) * 4,
				(GLvoid*)(sizeof(float) * 2)
			);
			break;
		case mg::VertexFormat::PPPNNN:
			if(pos == -1) {
				printf("batch failed to find v_pos shader attribute.\n");
				return false;
			}
			if(normal == -1) {
				printf("batch failed to find v_normal shader attribute.\n");
				return false;
			}

			glEnableVertexAttribArray(pos);
			glEnableVertexAttribArray(normal);

			glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBuffer());

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

GLuint mg::Batch::getVAO() const {
	return _vao;
}

std::shared_ptr<mg::Mesh> mg::Batch::getMesh() const {
	return _mesh;
}
std::shared_ptr<mg::ShaderUniforms> mg::Batch::getUniforms() const {
	return _uniforms;
}
std::shared_ptr<mg::Texture> mg::Batch::getTexture() const {
	return _texture;
}
std::shared_ptr<mg::Shader> mg::Batch::getShader() const {
	return _shader;
}
