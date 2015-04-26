#include "gfx/texture.hpp"

void gfx::Texture::createID() {
    if(!this->hasValidID()) {
        glGenTextures(1, &this->id);
    }
}
void gfx::Texture::deleteID() {
    if(this->hasValidID()) {
        glDeleteTextures(1, &this->id);
    }
}
void gfx::Texture::bindID() {
    if(this->hasValidID()) {
        glBindTexture(GL_TEXTURE_2D, this->id);
    }
}
bool gfx::Texture::hasValidID() {
    if(glIsTexture(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}
