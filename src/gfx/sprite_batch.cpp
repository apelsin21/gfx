#include "gfx/sprite_batch.hpp"

gfx::SpriteBatch::SpriteBatch() {
	this->max = 10000; //max sprites to be able to render. this is only 0.2 mb vram
	this->current = 0;

	this->pos_vbo = 0;
	this->uv_vbo = 0;
	this->vao = 0;
	this->defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
gfx::SpriteBatch::SpriteBatch(unsigned int max) {
	this->max = max;
	this->current = 0;

	this->pos_vbo = 0;
	this->uv_vbo = 0;
	this->vao = 0;
	this->defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
gfx::SpriteBatch::~SpriteBatch() {
	if(glIsVertexArray(this->vao) == GL_TRUE) {
    	glDeleteVertexArrays(1, &this->vao);
	}
	if(glIsBuffer(this->pos_vbo) == GL_TRUE) {
    	glDeleteBuffers(1, &this->pos_vbo);
	}
	if(glIsBuffer(this->uv_vbo) == GL_TRUE) {
    	glDeleteBuffers(1, &this->uv_vbo);
	}
	if(glIsBuffer(this->vbo) == GL_TRUE) {
		glDeleteBuffers(1, &this->vbo);
	}
}

void gfx::SpriteBatch::initialize(int v_pos, int v_uv) {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	int totalBufferSize = (sizeof(float)*7)*this->max;
	glBufferData(GL_ARRAY_BUFFER, totalBufferSize, NULL, GL_DYNAMIC_DRAW); 

    glEnableVertexAttribArray(v_pos);
    glVertexAttribPointer(v_pos, 3, GL_FLOAT, GL_FALSE, sizeof(float)*7, (GLvoid*)0);
	glVertexAttribDivisor(v_pos, 1);

    glEnableVertexAttribArray(v_uv);
    glVertexAttribPointer(v_uv, 4, GL_FLOAT, GL_FALSE, sizeof(float)*7, (GLvoid*)(sizeof(float)*3)); 
	glVertexAttribDivisor(v_uv, 1);
}

void gfx::SpriteBatch::draw(const glm::vec2& pos, float scale, const glm::vec4& uv) {
	if(this->current >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max);
		return;
	}

	this->tempBuffer.emplace_back(pos.x);
	this->tempBuffer.emplace_back(pos.y);
	this->tempBuffer.emplace_back(scale);
	this->tempBuffer.emplace_back(uv.x);
	this->tempBuffer.emplace_back(uv.y);
	this->tempBuffer.emplace_back(uv.z);
	this->tempBuffer.emplace_back(uv.w);
	
	this->current++;
}

void gfx::SpriteBatch::drawAll() {
	glBindVertexArray(this->vao);

	printf("current: %u\n", this->current);
	printf("buffer.size(): %u\n", this->tempBuffer.size() * (sizeof(float)));
	printf("should be: %u\n", this->current * (sizeof(float)*7));
	printf("vbo update size %f KB\n", (sizeof(float)*7.0f)*(float)this->current / 1024.0f);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(float)*7)*this->current, (GLvoid*)&this->tempBuffer[0]);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->current);

	this->tempBuffer.clear();
	this->current = 0;
}
