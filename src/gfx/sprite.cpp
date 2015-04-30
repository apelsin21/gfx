#include "gfx/sprite.hpp"

gfx::Sprite::Sprite() {
    float posArray[] = {
        -1.0f, -1.0f, //Bottom left
         1.0f, -1.0f, //Bottom right
        -1.0f,  1.0f, //Top left

         1.0f, -1.0f, //Bottom right
         1.0f,  1.0f, //Top right
        -1.0f,  1.0f, //Top left
    };
    float uvArray[] = {
         0.0f,  0.0f, //Bottom left
         1.0f,  0.0f, //Bottom right
         0.0f,  1.0f, //Top left

         1.0f,  0.0f, //Bottom right
         1.0f,  1.0f, //Top right
         0.0f,  1.0f, //Top left
    };
    float colorArray[] = {
         1.0f,  1.0f, 1.0f, 1.0f, //Bottom left
         1.0f,  1.0f, 1.0f, 1.0f, //Bottom right
         1.0f,  1.0f, 1.0f, 1.0f, //Top left
                            
         1.0f,  1.0f, 1.0f, 1.0f, //Bottom left
         1.0f,  1.0f, 1.0f, 1.0f, //Bottom right
         1.0f,  1.0f, 1.0f, 1.0f, //Top right
    };

	std::memcpy(this->positions, posArray, sizeof(posArray));
	std::memcpy(this->uvs, uvArray, sizeof(uvArray));
	std::memcpy(this->colors, colorArray, sizeof(colorArray));
}
gfx::Sprite::~Sprite() {
}
