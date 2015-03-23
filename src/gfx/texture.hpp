#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <FreeImage.h>

namespace gfx {
    class Texture {
        private:
            int width, height, bpp;
            std::string path;
        public:
            Texture();
            ~Texture();

            FREE_IMAGE_FORMAT getFreeImageFormatFromPath(const std::string&);
            bool load(const std::string&);
    };
}

#endif //TEXTURE_HPP
