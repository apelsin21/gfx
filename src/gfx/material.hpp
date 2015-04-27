#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

#include "gfx/texture.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/color.hpp"

namespace gfx {
    class Material {
        public:
            Texture diffuseTexture, normalTexture, specularTexture;
            ShaderProgram shaderProgram;
            Color color;

            Material();
            ~Material();
    };
}

#endif //MATERIAL_HPP
