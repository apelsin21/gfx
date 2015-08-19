#include "gfx/sprite_batch.hpp"

mg::SpriteBatch::SpriteBatch() {
	this->max = 10000; //max sprites to be able to render. this is only 0.2 mb vram
	this->current = 0;

	this->tempBuffer = new float[this->max];

	this->vbo = 0;
	this->vao = 0;
	this->defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
mg::SpriteBatch::SpriteBatch(unsigned int max) {
	this->max = max;
	this->current = 0;
	this->tempBuffer = new float[this->max];

	this->vbo = 0;
	this->vao = 0;
	this->defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
mg::SpriteBatch::~SpriteBatch() {
	if(glIsVertexArray(this->vao) == GL_TRUE) {
    	glDeleteVertexArrays(1, &this->vao);
	}
	if(glIsBuffer(this->vbo) == GL_TRUE) {
		glDeleteBuffers(1, &this->vbo);
	}

	if(this->tempBuffer) {
		delete this->tempBuffer;
	}
}

bool mg::SpriteBatch::initialize(int v_pos, int v_uv) {
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

void mg::SpriteBatch::draw(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& uv) {
	if((this->current/8) >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max);
		return;
	}

	this->tempBuffer[this->current] = pos.x;
	this->tempBuffer[this->current + 1] = pos.y;
	this->tempBuffer[this->current + 2] = scale.x;
	this->tempBuffer[this->current + 3] = scale.y;
	this->tempBuffer[this->current + 4] = uv.x;
	this->tempBuffer[this->current + 5] = uv.y;
	this->tempBuffer[this->current + 6] = uv.z;
	this->tempBuffer[this->current + 7] = uv.w;

	this->current += 8;
}
void mg::SpriteBatch::draw(const std::wstring& text, mg::Font& font, const glm::vec2& pos, float size) {
	glm::vec2 pen = pos;

	for(unsigned int i = 0; i < text.size(); i++) {
		mg::Glyph glyph = font.glyphs[text[i]];

		this->draw(
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

void mg::SpriteBatch::drawAll(unsigned int texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*this->current, (GLvoid*)this->tempBuffer);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->current/8);

	this->current = 0;
}
