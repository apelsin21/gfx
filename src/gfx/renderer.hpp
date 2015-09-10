#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <epoxy/gl.h>

#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "gfx/renderer.hpp"
#include "gfx/batch.hpp"
#include "gfx/mesh.hpp"
#include "gfx/shader_uniforms.hpp"
#include "gfx/framebuffer.hpp"

namespace mg {
	class Renderer {
		protected:
			glm::vec2 _res;
			glm::vec4 _clearColor;

			GLuint _vao;
		public:
			Renderer();
			~Renderer();

			void setClearColor(const glm::vec4&);
			glm::vec4 getClearColor() const;

			void setSize(const glm::vec2&);
			glm::vec2 getSize() const;

			bool render(std::shared_ptr<mg::FrameBuffer>, std::shared_ptr<mg::Batch>);
			bool render(std::shared_ptr<mg::Batch>);
	};
}

#endif //RENDERER_HPP
