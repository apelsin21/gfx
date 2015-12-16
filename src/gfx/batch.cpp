#include "gfx/batch.hpp"

mg::Batch::Batch() {
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
}
mg::Batch::~Batch() {
	if(glIsVertexArray(m_vao) == GL_TRUE) {
		glDeleteVertexArrays(1, &m_vao);
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

	m_mesh 		=	std::move(mesh		);
	m_uniforms 	= 	std::move(uniforms	);
	m_texture 	= 	std::move(texture	);
	m_shader    =	std::move(shader	);

	if(glIsVertexArray(m_vao) == GL_FALSE) {
		printf("batch failed to bind VAO.\n");
		return false;
	}
	if(glIsBuffer(m_mesh->getVertexBuffer()) == GL_FALSE) {
		printf("batch failed to bind mesh vertex buffer.\n");
		return false;
	}

	glBindVertexArray(m_vao);

	GLint pos = m_shader->getAttribLocation("v_pos");
	GLint normal = m_shader->getAttribLocation("v_normal");
	GLint uv = m_shader->getAttribLocation("v_uv");

	switch(m_mesh->getVertexFormat()) {
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

			glBindBuffer(GL_ARRAY_BUFFER, m_mesh->getVertexBuffer());

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

			glBindBuffer(GL_ARRAY_BUFFER, m_mesh->getVertexBuffer());

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
	return m_vao;
}

std::shared_ptr<mg::Mesh> mg::Batch::getMesh() const {
	return m_mesh;
}
std::shared_ptr<mg::ShaderUniforms> mg::Batch::getUniforms() const {
	return m_uniforms;
}
std::shared_ptr<mg::Texture> mg::Batch::getTexture() const {
	return m_texture;
}
std::shared_ptr<mg::Shader> mg::Batch::getShader() const {
	return m_shader;
}
