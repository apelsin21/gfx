#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include <memory>
#include <vector>

#include <epoxy/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gfx/font.hpp"
#include "gfx/gl_vertex_buffer.hpp"

namespace mg {
	class SpriteBatch {
		public:
			GLuint _vao, m_vbo;
			unsigned int m_updateDelta;

			unsigned int _max, _current;
			glm::vec4 _defaultUV;
			std::vector<float> _tempBuffer;

			SpriteBatch();
			SpriteBatch(unsigned int);
			~SpriteBatch();

			bool initialize(int, int);

			void add(const glm::vec2&, const glm::vec2&, const glm::vec4&);
			void add(const std::wstring&, mg::Font&, const glm::vec2&, float size);

			std::shared_ptr<mg::GLVertexBuffer> getBuffer() const;

			void drawAll(unsigned int);
	};
}

#endif //SPRITE_BATCH_HPP
