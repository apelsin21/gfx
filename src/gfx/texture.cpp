#include "gfx/texture.hpp"

gfx::Texture::Texture() {
    this->mipmaps = true;

    this->minFilter = TEXTURE_FILTER::TEXTURE_FILTER_NEAREST;
    this->magFilter = TEXTURE_FILTER::TEXTURE_FILTER_NEAREST;
    this->sWrap = TEXTURE_WRAP::TEXTURE_WRAP_REPEAT;
    this->tWrap = TEXTURE_WRAP::TEXTURE_WRAP_REPEAT;
}

void gfx::Texture::createID() {
    if(!this->hasValidID()) {
        glGenTextures(1, &this->id);
        this->bindID(); //Texture name isn't valid until bound
    }
}
void gfx::Texture::deleteID() {
    if(this->hasValidID()) {
        glDeleteTextures(1, &this->id);
    }
}
void gfx::Texture::bindID() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
bool gfx::Texture::hasValidID() {
    if(glIsTexture(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}

GLenum gfx::Texture::textureFilterToGLEnum(TEXTURE_FILTER t) {
    switch(t) {
    case TEXTURE_FILTER::TEXTURE_FILTER_NEAREST:
        return GL_NEAREST;
    break;
    case TEXTURE_FILTER::TEXTURE_FILTER_LINEAR:
        return GL_LINEAR;
    break;
    }
}
GLenum gfx::Texture::textureWrapToGLEnum(TEXTURE_WRAP t) {
    switch(t) {
    case TEXTURE_WRAP::TEXTURE_WRAP_REPEAT:
        return GL_REPEAT;
    break;
    case TEXTURE_WRAP::TEXTURE_WRAP_MIRRORED_REPEAT:
        return GL_MIRRORED_REPEAT;
    break;
    case TEXTURE_WRAP::TEXTURE_WRAP_CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
    break;
    case TEXTURE_WRAP::TEXTURE_WRAP_CLAMP_TO_BORDER:
        return GL_CLAMP_TO_BORDER;
    break;
    }
}
