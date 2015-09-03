#include "gfx/shader_uniforms.hpp"

mg::ShaderUniforms::ShaderUniforms() {
}
mg::ShaderUniforms::~ShaderUniforms() {
}

void mg::ShaderUniforms::add(const std::string& key, std::shared_ptr<float> val) {
	_floats[key] = val;
}
void mg::ShaderUniforms::add(const std::string& key, std::shared_ptr<glm::vec2> val) {
	_vec2s[key] = val;
}
void mg::ShaderUniforms::add(const std::string& key, std::shared_ptr<glm::vec3> val) {
	_vec3s[key] = val;
}
void mg::ShaderUniforms::add(const std::string& key, std::shared_ptr<glm::vec4> val) {
	_vec4s[key] = val;
}
void mg::ShaderUniforms::add(const std::string& key, float* val) {
	_matrices[key] = val;
}

const std::unordered_map<std::string, std::shared_ptr<float>>& mg::ShaderUniforms::getFloats() const {
	return _floats;
}
const std::unordered_map<std::string, std::shared_ptr<glm::vec2>>& mg::ShaderUniforms::getVec2s() const {
	return _vec2s;
}
const std::unordered_map<std::string, std::shared_ptr<glm::vec3>>& mg::ShaderUniforms::getVec3s() const {
	return _vec3s;
}
const std::unordered_map<std::string, std::shared_ptr<glm::vec4>>& mg::ShaderUniforms::getVec4s() const {
	return _vec4s;
}
const std::unordered_map<std::string, float*>& mg::ShaderUniforms::getMatrices() const {
	return _matrices;
}
