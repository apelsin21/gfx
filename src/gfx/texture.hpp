#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

namespace gfx {
    class Texture {
        public:
            int width, height, bpp;
            std::string path;

            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
            virtual int getBPP() = 0;

            virtual std::string getPath() = 0;

            virtual bool load(const std::string&) = 0;
    };
}

#endif //TEXTURE_HPP
