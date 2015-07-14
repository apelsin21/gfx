#include "gfx/texture.hpp"

mg::Texture::Texture() {
    mipmaps = false;
    bpp = 0;

    minFilter = mg::TEXTURE_FILTER::NEAREST;
    magFilter = mg::TEXTURE_FILTER::NEAREST;
    sWrap = mg::TEXTURE_WRAP::REPEAT;
    tWrap = mg::TEXTURE_WRAP::REPEAT;
}
