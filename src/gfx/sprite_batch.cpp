#include "gfx/sprite_batch.hpp"

mg::SpriteBatch::SpriteBatch() {
	this->max = 10000; //max sprites to be able to render. this is only 0.2 mb vram
	this->current = 0;

	this->vbo = 0;
	this->vao = 0;
	this->defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
mg::SpriteBatch::SpriteBatch(unsigned int max) {
	this->max = max;
	this->current = 0;

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
}

void mg::SpriteBatch::initialize(int v_pos, int v_uv) {
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
    glVertexAttribPointer(v_uv, 4, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float)*4)); 
	glVertexAttribDivisor(v_uv, 1);

	this->tempBuffer.reserve(this->max * 7);
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
void mg::SpriteBatch::draw(const std::wstring& text, mg::Font& font, const glm::vec2& pos) {
	glm::vec2 pen = pos; 

	for(unsigned int i = 0; i < text.size(); i++) {
		mg::Glyph glyph = font.glyphs[text[i]];

		float w = glyph.resolution.x;
		float h = glyph.resolution.y;

		float x2 = pen.x + glyph.left;
		float y2 = -pen.y - glyph.top;

		pen.x += glyph.advance.x*2.0f;
		pen.y += glyph.advance.y;

		if(!w || !h) {
			continue;
		}

		this->draw(
				glm::vec2(x2 + (w/2.0f), -y2 - (h/2.0f)),
			   	glm::vec2(w, h),
			   	glyph.uvs
		);
	}
}

void mg::SpriteBatch::drawAll() {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*this->current, (GLvoid*)&this->tempBuffer[0]);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->current/8);

	this->current = 0;
}
