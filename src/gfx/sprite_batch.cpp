#include "gfx/sprite_batch.hpp"

mg::SpriteBatch::SpriteBatch() {
	_max = 10000;
	_current = 0;

	_tempBuffer = std::vector<float>(_max);

	_vao = 0;
	_defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
mg::SpriteBatch::SpriteBatch(unsigned int max) {
	_max = max;
	_current = 0;
	_tempBuffer = std::vector<float>(_max);

	_vao = 0;
	_defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
mg::SpriteBatch::~SpriteBatch() {
	if(glIsVertexArray(_vao) == GL_TRUE) {
    	glDeleteVertexArrays(1, &_vao);
	}
}

bool mg::SpriteBatch::initialize(int v_pos, int v_uv) {
	if(v_pos <= -1 || v_uv <= -1) {
		printf("SpriteBatch got invalid shader attributes.\n");
		return false;
	}

    glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	if(!_buffer->allocate(sizeof(float) * 8 * _max, false)) {
		return false;
	}

    glEnableVertexAttribArray(v_pos);
    glVertexAttribPointer(v_pos, 4, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)0);
	glVertexAttribDivisor(v_pos, 1);

    glEnableVertexAttribArray(v_uv);
    glVertexAttribPointer(v_uv, 4, GL_FLOAT, GL_TRUE, sizeof(float)*8, (GLvoid*)(sizeof(float)*4));
	glVertexAttribDivisor(v_uv, 1);

	return true;
}

void mg::SpriteBatch::add(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& uv) {
	if((_current/8) >= _max) {
		printf("spritebatch can't render more than %u sprites\n", _max);
		return;
	}

	_tempBuffer[_current] = pos.x;
	_tempBuffer[_current + 1] = pos.y;
	_tempBuffer[_current + 2] = scale.x;
	_tempBuffer[_current + 3] = scale.y;
	_tempBuffer[_current + 4] = uv.x;
	_tempBuffer[_current + 5] = uv.y;
	_tempBuffer[_current + 6] = uv.z;
	_tempBuffer[_current + 7] = uv.w;

	_current += 8;
}
void mg::SpriteBatch::add(const std::wstring& text, mg::Font& font, const glm::vec2& pos, float size) {
	glm::vec2 pen = pos;

	for(unsigned int i = 0; i < text.size(); i++) {
		mg::Glyph glyph = font.glyphs[text[i]];

		this->add(
			glm::vec2(pen.x + glyph.left + glyph.resolution.x, pen.y - (glyph.top + glyph.advance.y - glyph.resolution.y)),
			glm::vec2(glyph.resolution.x, glyph.resolution.y),
			glyph.uvs
		);

		if(text[i] == '\n') { //newline
			pen = glm::vec2(pos.x, pen.y - (font.resolution.y*2.0f));
		} else if(text[i] == '\t') { //tab
			pen.x += (glyph.advance.x*2.0f) + (font.glyphs[' '].advance.x * 8.0f);
		} else { //a normal character
			pen.x += glyph.advance.x*2.0f;
		}
	}
}

std::shared_ptr<mg::GLVertexBuffer> mg::SpriteBatch::getBuffer() const {
	return _buffer;
}

void mg::SpriteBatch::update() {
	_buffer->updateRegion(_tempBuffer, 0, sizeof(float) * _current);
}

//void mg::SpriteBatch::drawAll(unsigned int texture) {
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glBindVertexArray(_vao);
//
//	if(_buffer->updateRegion(_tempBuffer, 0, sizeof(float) * _current)) {
//		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, _current/8);
//	} else {
//		printf("Failed to update spritebatch vertexbuffer.\n");
//		return;
//	}
//
//	_current = 0;
//}
