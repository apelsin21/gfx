#ifndef SHADER_UNIFORMS_HPP
#define SHADER_UNIFORMS_HPP

#include <unordered_map>
#include <string>
#include <memory>

#include <glm/glm.hpp>

namespace mg {
	class ShaderUniforms {
		protected:
			std::unordered_map<std::string, std::shared_ptr<float>> _floats;
			std::unordered_map<std::string, std::shared_ptr<glm::vec2>> _vec2s;
			std::unordered_map<std::string, std::shared_ptr<glm::vec3>> _vec3s;
			std::unordered_map<std::string, std::shared_ptr<glm::vec4>> _vec4s;
			std::unordered_map<std::string, float*> _matrices;
		public:
			ShaderUniforms();
			~ShaderUniforms();

			void add(const std::string&, std::shared_ptr<float>);
			void add(const std::string&, std::shared_ptr<glm::vec2>);
			void add(const std::string&, std::shared_ptr<glm::vec3>);
			void add(const std::string&, std::shared_ptr<glm::vec4>);
			void add(const std::string&, float*);

			const std::unordered_map<std::string, std::shared_ptr<float>>& getFloats() const;
			const std::unordered_map<std::string, std::shared_ptr<glm::vec2>>& getVec2s() const;
			const std::unordered_map<std::string, std::shared_ptr<glm::vec3>>& getVec3s() const;
			const std::unordered_map<std::string, std::shared_ptr<glm::vec4>>& getVec4s() const;
			const std::unordered_map<std::string, float*>& getMatrices() const;
	};
}

#endif //SHADER_UNIFORMS_HPP
