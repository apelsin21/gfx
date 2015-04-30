#include "gfx/sprite_manager.hpp"

gfx::SpriteManager::SpriteManager() {
	this->maxSprites = 10000;
	this->numSprites = 0;

	this->pos_vbo = 0;
	this->uv_vbo = 0;
	this->color_vbo = 0;
	this->vao = 0;
}
gfx::SpriteManager::SpriteManager(unsigned int max) {
	this->maxSprites = max;
	this->numSprites = 0;

	this->pos_vbo = 0;
	this->uv_vbo = 0;
	this->color_vbo = 0;
	this->vao = 0;
}
gfx::SpriteManager::~SpriteManager() {
	if(glIsVertexArray(this->vao) == GL_TRUE) {
    	glDeleteVertexArrays(1, &this->vao);
	}
	if(glIsBuffer(this->color_vbo) == GL_TRUE) {
    	glDeleteBuffers(1, &this->color_vbo);
	}
	if(glIsBuffer(this->uv_vbo) == GL_TRUE) {
    	glDeleteBuffers(1, &this->uv_vbo);
	}
	if(glIsBuffer(this->pos_vbo) == GL_TRUE) {
    	glDeleteBuffers(1, &this->pos_vbo);
	}
}

void gfx::SpriteManager::initialize(int v_pos, int v_uv, int v_color) {
    glGenBuffers(1, &this->pos_vbo);
    glGenBuffers(1, &this->uv_vbo);
    glGenBuffers(1, &this->color_vbo);
    glGenVertexArrays(1, &this->vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12*this->maxSprites, NULL, GL_STATIC_DRAW);
    glEnableVertexAttribArray(v_pos);
    glVertexAttribPointer(v_pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12*this->maxSprites, NULL, GL_STATIC_DRAW);
    glEnableVertexAttribArray(v_uv);
    glVertexAttribPointer(v_uv, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, this->color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24*this->maxSprites, NULL, GL_STATIC_DRAW);
    glEnableVertexAttribArray(v_color);
    glVertexAttribPointer(v_color, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
}

gfx::Sprite gfx::SpriteManager::getSprite() {
	gfx::Sprite sprite;

	if(this->numSprites >= this->maxSprites) {
		printf("can't add more sprites to spritemanager, max number of %u reached!\n", this->maxSprites);
		return sprite;
	}

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->numSprites*sizeof(sprite.positions), sizeof(sprite.positions), sprite.positions);

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->numSprites*sizeof(sprite.uvs), sizeof(sprite.uvs), sprite.uvs);

	glBindBuffer(GL_ARRAY_BUFFER, this->color_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->numSprites*sizeof(sprite.colors), sizeof(sprite.colors), sprite.colors);

	this->numSprites++;

	return sprite;
}

void gfx::SpriteManager::addSprite() {
	gfx::Sprite sprite;

	if(this->numSprites >= this->maxSprites) {
		printf("can't add more sprites to spritemanager, max number of %u reached!\n", this->maxSprites);
		return;
	}

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->numSprites*sizeof(sprite.positions), sizeof(sprite.positions), sprite.positions);

	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->numSprites*sizeof(sprite.uvs), sizeof(sprite.uvs), sprite.uvs);

	glBindBuffer(GL_ARRAY_BUFFER, this->color_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, this->numSprites*sizeof(sprite.colors), sizeof(sprite.colors), sprite.colors);

	this->numSprites++;
}
