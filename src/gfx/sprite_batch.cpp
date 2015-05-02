#include "gfx/sprite_batch.hpp"

gfx::SpriteBatch::SpriteBatch() {
	this->max = 10000;
	this->current = 0;

	this->pos_vbo = 0;
	this->uv_vbo = 0;
	this->vao = 0;
}
gfx::SpriteBatch::SpriteBatch(unsigned int max) {
	this->max = max;
	this->current = 0;

	this->pos_vbo = 0;
	this->uv_vbo = 0;
	this->vao = 0;
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
}

void gfx::SpriteBatch::initialize(int v_pos, int v_uv) {
    glGenBuffers(1, &this->pos_vbo);
    glGenBuffers(1, &this->uv_vbo);
    glGenVertexArrays(1, &this->vao);

	float pos[] = {
		0.0f, 0.0f, 1.0f,
	};

	float uvs[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
	};

	glBindVertexArray(this->vao);

	//Pos
	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*this->max, NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(pos), pos);

    glEnableVertexAttribArray(v_pos);
    glVertexAttribPointer(v_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribDivisor(v_pos, 1);


	//UV
	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs)*this->max, NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(uvs), uvs);

    glEnableVertexAttribArray(v_uv);
    glVertexAttribPointer(v_uv, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
}

void gfx::SpriteBatch::draw(gfx::Texture& tex, const glm::vec2& pos) {
	if(this->current >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max);
		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*(sizeof(float)*3), sizeof(float)*3, glm::value_ptr(glm::vec3(pos.x, pos.y, 1.0f)));

	float uvs[] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		
		0.5f, 0.0f,
		0.5f, 0.5f,
		0.0f, 0.5f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*sizeof(uvs), sizeof(uvs), uvs);

	this->current++;
}
void gfx::SpriteBatch::draw(gfx::Texture& tex, const glm::vec2& pos, float scale) {
	if(this->current >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max);
		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*(sizeof(float)*3), sizeof(float)*3, glm::value_ptr(glm::vec3(pos.x, pos.y, scale)));

	float uvs[] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		
		0.5f, 0.0f,
		0.5f, 0.5f,
		0.0f, 0.5f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*sizeof(uvs), sizeof(uvs), uvs);

	this->current++;
}

void gfx::SpriteBatch::drawAll() {
	glBindVertexArray(this->vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->current);

	this->current = 0;
}
