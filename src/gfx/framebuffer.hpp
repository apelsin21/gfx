#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <epoxy/gl.h>

#include <glm/glm.hpp>

#include "gfx/texture.hpp"

namespace mg {
	class FrameBuffer {
		protected:
			GLuint _fbo;
			GLuint _rboDepth, _rboColor;

			std::shared_ptr<mg::Texture> _colorTexture;
		public:
			FrameBuffer();
			~FrameBuffer();

			bool createColorTexture(const glm::vec2&);
			std::shared_ptr<mg::Texture> getColorTexture() const;


			bool isComplete() const;

			GLuint getGLHandle() const;
	};
}

#endif //FRAMEBUFFER_HPP
