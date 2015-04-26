#ifndef GL_SHADER_PROGRAM_HPP
#define GL_SHADER_PROGRAM_HPP

#include <stdio.h>
#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

#include "gfx/shader.hpp"

namespace gfx {
    class ShaderProgram {
        protected:
        public:
            unsigned int id;
            gfx::Shader vs, fs, geom, tess;
            bool loaded, linked;

            ShaderProgram();
            ~ShaderProgram();
            
            void createID();
            void deleteID();
            bool hasValidID();

            bool attachShader(const Shader&);

            bool loadFromPaths(const std::string&, const std::string&);
            bool loadFromMemory(const std::string&, const std::string&);

            bool link();
    };
}

#endif //GL_SHADER_PROGRAM_HPP
