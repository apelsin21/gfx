#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <fstream>
#include <memory>

#include <glm/glm.hpp>

#include <FreeImage.h>

#include <epoxy/gl.h>

namespace mg {
    enum class TextureFilter {
        Nearest,
        Linear,
    };
    enum class TextureWrap {
        Repeat,
        Mirrored_Repeat,
        Clamp_To_Edge,
        Clamp_To_Border,
    };
    enum class TextureFormat {
        RGBA8,
        BGRA,
		RGB,
		RGBA,
    };

    class Texture {
		protected:
			unsigned int _id;
            int _textureFilterToInt(mg::TextureFilter);
            int _textureWrapToInt(mg::TextureWrap);
            int _textureFormatToInt(mg::TextureFormat);

			mg::TextureFilter _filter;
            mg::TextureWrap _wrap;
            mg::TextureFormat _format, _internalFormat;
            glm::vec2 _resolution;
            std::string _path;
			unsigned int _size, _bpp;
            bool _mipmaps;
        public:
            Texture();
			~Texture();

			bool upload(unsigned char*);

			void setSize(unsigned int);
			unsigned int getSize() const;

			void setBPP(unsigned int);
			unsigned int getBPP() const;

			void setPath(const std::string&);
			std::string getPath() const;

			void setResolution(const glm::vec2&);
			glm::vec2 getResolution() const;

			void setFilter(mg::TextureFilter);
			mg::TextureFilter getFilter() const;

			void setWrap(mg::TextureWrap);
			mg::TextureWrap getWrap() const;

			void setFormat(mg::TextureFormat);
			mg::TextureFormat getFormat() const;

			void setInternalFormat(mg::TextureFormat);
			mg::TextureFormat getInternalFormat() const;

			void setIsMipMapped(bool);
			bool isMipMapped() const;

			void setGLHandle(unsigned int);
			unsigned int getGLHandle() const;
    };
}

#endif //TEXTURE_HPP
