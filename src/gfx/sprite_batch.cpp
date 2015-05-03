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
}

void gfx::SpriteBatch::initialize(int v_pos, int v_uv) {
    glGenBuffers(1, &this->pos_vbo);
    glGenBuffers(1, &this->uv_vbo);
    glGenVertexArrays(1, &this->vao);

	glBindVertexArray(this->vao);

	//Pos
	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	//NULL is where the data normally would go, but we send nothing and update it later.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*this->max, NULL, GL_DYNAMIC_DRAW); 
    glEnableVertexAttribArray(v_pos);
	//positions have 3 components, are floats, not normalized and are right after each other
    glVertexAttribPointer(v_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribDivisor(v_pos, 1); //only one unique attribute per object

	//UV
	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	//NULL is where the data normally would go, but we send nothing and update it later.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*this->max, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(v_uv);
	//texture coordinates have 4 components, are floats, not normalized and are right after each other
    glVertexAttribPointer(v_uv, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); 
	glVertexAttribDivisor(v_uv, 1); //only one unique attribute per object
}

//Duplicated code galore
void gfx::SpriteBatch::draw(const glm::vec2& pos) {
	if(this->current >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max); //so that we don't update out of buffer bounds
		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo); //contains x, y, and scale. makes 3 floats
	//updates the buffer with the new position, with the size of 3 floats, and the default scale
	glBufferSubData(GL_ARRAY_BUFFER, this->current*sizeof(float)*3, sizeof(float)*3, glm::value_ptr(glm::vec3(pos.x, pos.y, 1.0f)));

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	//updates the buffer with the new texture coordinate, size of 4 floats, and the default texture coordinate
	//this may seem redundant, but otherwise we might get 0.0f, 0.0f, 0.0f, 0.0f as texture coordinates and it would only be
	//one pixel of the texture, or it may be the value of a texture coordinate of another sprite
	glBufferSubData(GL_ARRAY_BUFFER, this->current*sizeof(float)*4, sizeof(float)*4, glm::value_ptr(this->defaultUV));

	this->current++;
}
void gfx::SpriteBatch::draw(const glm::vec2& pos, float scale) {
	if(this->current >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max);
		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*(sizeof(float)*3), sizeof(float)*3, glm::value_ptr(glm::vec3(pos.x, pos.y, scale)));

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*sizeof(float)*4, sizeof(float)*4, glm::value_ptr(this->defaultUV));

	this->current++;
}
void gfx::SpriteBatch::draw(const glm::vec2& pos, float scale, const glm::vec4& uv) {
	if(this->current >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max);
		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*(sizeof(float)*3), sizeof(float)*3, glm::value_ptr(glm::vec3(pos.x, pos.y, scale)));

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->current*sizeof(float)*4, sizeof(float)*4, glm::value_ptr(uv));

	this->current++;
}

void gfx::SpriteBatch::drawAll() {
	glBindVertexArray(this->vao);
	//draws (this->current*2) triangles
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->current);

	this->current = 0;
}
