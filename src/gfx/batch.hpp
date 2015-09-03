#ifndef BATCH_HPP
#define BATCH_HPP

#include <memory>

#include <epoxy/gl.h>

#include "gfx/mesh.hpp"
#include "gfx/shader_uniforms.hpp"
#include "gfx/gl_texture.hpp"
#include "gfx/gl_shader.hpp"

namespace mg {
	class Batch {
		protected:
			std::shared_ptr<mg::Mesh>           _mesh;
			std::shared_ptr<mg::ShaderUniforms> _uniforms;
			std::shared_ptr<mg::GLTexture>  	_texture;
			std::shared_ptr<mg::GLShader>       _shader;

			unsigned int _vao;
		public:
			Batch();
			~Batch();

			bool set(
				const std::shared_ptr<mg::Mesh>&,
				const std::shared_ptr<mg::ShaderUniforms>&,
				const std::shared_ptr<mg::GLTexture>&,
				const std::shared_ptr<mg::GLShader>&
			);

			std::shared_ptr<mg::Mesh> getMesh() const;
			std::shared_ptr<mg::ShaderUniforms> getUniforms() const;
			std::shared_ptr<mg::GLTexture> getTexture() const;
			std::shared_ptr<mg::GLShader> getShader() const;
	};
}

#endif //BATCH_HPP
