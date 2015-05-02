#include "gfx/sprite.hpp"

gfx::Sprite::Sprite(int v_pos, int v_uv) {
	float data[] = {
    	-1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
	};              

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(v_pos);
	glEnableVertexAttribArray(v_uv);

	glVertexAttribPointer(v_pos, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (GLvoid*)0);
	glVertexAttribPointer(v_uv,  2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (GLvoid*)(sizeof(float)*2));
}
gfx::Sprite::~Sprite() {
	if(glIsVertexArray(this->vao) == GL_TRUE) {
		glDeleteVertexArrays(1, &this->vao);
	}
	if(glIsBuffer(this->vbo) == GL_TRUE) {
		glDeleteBuffers(1, &this->vbo);
	}
}

void gfx::Sprite::draw() {
	this->texture.bindID();
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
