#include "gfx/gl_renderer.hpp"

mg::GLRenderer::GLRenderer() {
}
mg::GLRenderer::~GLRenderer() {
}

bool mg::GLRenderer::initialize() {
	if(v_pos <= -1 || v_uv <= -1) {
		printf("SpriteBatch got invalid shader attributes.\n");
		return false;
	}

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	int totalBufferSize = (sizeof(float)*8)*this->max;
	glBufferData(GL_ARRAY_BUFFER, totalBufferSize, NULL, GL_STREAM_DRAW);

    glEnableVertexAttribArray(v_pos);
    glVertexAttribPointer(v_pos, 4, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)0);
	glVertexAttribDivisor(v_pos, 1);

    glEnableVertexAttribArray(v_uv);
    glVertexAttribPointer(v_uv, 4, GL_FLOAT, GL_TRUE, sizeof(float)*8, (GLvoid*)(sizeof(float)*4));
	glVertexAttribDivisor(v_uv, 1);

	return true;
}

bool mg::GLRenderer::render2D(const glm::vec2& p, const glm::vec2& s, const glm::vec4& t) {
	if((this->current/8) >= this->max) {
		printf("GLRenderer can't render more than %u sprites\n", _max);
		return false;
	}

	_tempBuffer[_current] = p.x;
	_tempBuffer[_current + 1] = p.y;
	_tempBuffer[_current + 2] = s.x;
	_tempBuffer[_current + 3] = s.y;
	_tempBuffer[_current + 4] = t.x;
	_tempBuffer[_current + 5] = t.y;
	_tempBuffer[_current + 6] = t.z;
	_tempBuffer[_current + 7] = t.w;

	_current += 8;

	return true;
}
