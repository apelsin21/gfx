#include "gfx/gl_renderer.hpp"

mg::GLRenderer::GLRenderer() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
mg::GLRenderer::~GLRenderer() {
	if(glIsVertexArray(_vao) == GL_TRUE) {
		glDeleteVertexArrays(1, &_vao);
	}
}

bool mg::GLRenderer::render(const mg::GLShader& shader, const mg::GLVertexBuffer& buffer) {
	if(buffer.getNumVertices() == 0 || buffer.getMaxVertices() == 0) {
		printf("Tried to render empty vertex buffer.\n");
		return false;
	}

	//GLint uvLocation = shader.getAttribLocation(_uvName);
	//GLint colorLocation = shader.getAttribLocation(_colorName);
	//GLint normalLocation = shader.getAttribLocation(_normalName);

	//if(uvLocation == -1) {
	//	printf("Failed to find shader attribute %s in shader %i.\n", _uvName, shader.getGLHandle());
	//	return false;
	//}
	//if(colorLocation == -1) {
	//	printf("Failed to find shader attribute %s in shader %i.\n", _colorName, shader.getGLHandle());
	//	return false;
	//}
	//if(normalLocation == -1) {
	//	printf("Failed to find shader attribute %s in shader %i.\n", _normalName, shader.getGLHandle());
	//	return false;
	//}

	shader.bind();
	glBindVertexArray(_vao);
	buffer.bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch(buffer.getFormat()) {
	case mg::VertexFormat::PPP:
		_posLocation = shader.getAttribLocation(_posName);

		if(_posLocation == -1) {
			printf("Failed to find shader attribute %s in shader %i.\n", _posName, shader.getGLHandle());
			return false;
		}

    	glEnableVertexAttribArray(_posLocation);

    	glVertexAttribPointer(_posLocation, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

		glDrawArrays(GL_TRIANGLES, 0, buffer.getNumVertices() / 3);

		break;
	case mg::VertexFormat::PPPTT:
		_posLocation = shader.getAttribLocation(_posName);
		_uvLocation = shader.getAttribLocation(_uvName);

		glEnableVertexAttribArray(_posLocation);
		glEnableVertexAttribArray(_uvLocation);

		glVertexAttribPointer(_posLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)0);
		glVertexAttribPointer(_uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

		glDrawArrays(GL_TRIANGLES, 0, buffer.getNumVertices() / 5);
		break;
	default:
		printf("GLRenderer tried to render unimplemented vertex format.\n");
		return false;
		break;
	}

	return true;
}
