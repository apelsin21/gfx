#include "gfx/shader.hpp"

mg::Shader::Shader() {
    loaded = false;
    linked = false;
}

bool mg::Shader::isLoaded() {
	return loaded;
}
bool mg::Shader::isLinked() {
	return linked;
}
