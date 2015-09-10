#ifndef BATCH_HPP
#define BATCH_HPP

#include <memory>

#include <epoxy/gl.h>

#include "gfx/mesh.hpp"
#include "gfx/shader_uniforms.hpp"
#include "gfx/texture.hpp"
#include "gfx/shader.hpp"

namespace mg {
	class Batch {
		protected:
			std::shared_ptr<mg::Mesh>           _mesh;
			std::shared_ptr<mg::ShaderUniforms> _uniforms;
			std::shared_ptr<mg::Texture>  		_texture;
			std::shared_ptr<mg::Shader>         _shader;

			GLuint _vao;
		public:
			Batch();
			~Batch();

			bool set(
				std::shared_ptr<mg::Mesh>,
				std::shared_ptr<mg::ShaderUniforms>,
				std::shared_ptr<mg::Texture>,
				std::shared_ptr<mg::Shader>
			);

			GLuint getVAO() const;

			std::shared_ptr<mg::Mesh> getMesh() const;
			std::shared_ptr<mg::ShaderUniforms> getUniforms() const;
			std::shared_ptr<mg::Texture> getTexture() const;
			std::shared_ptr<mg::Shader> getShader() const;
	};
}

#endif //BATCH_HPP
