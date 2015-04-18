#ifndef GL_SHADER_PROGRAM_HPP
#define GL_SHADER_PROGRAM_HPP

#include <stdio.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "gfx/gl_shader.hpp"

namespace gfx {
    class GLShaderProgram {
        protected:
        public:
            unsigned int id;
            gfx::GLShader vs, fs, geom, tess;
            bool loaded, linked; //true means it has been done successfully

            GLShaderProgram();
            ~GLShaderProgram();
            
            void createID();
            void deleteID();
            bool hasValidID();

            bool attachShader(const GLShader&);

            bool loadFromPaths(const std::string&, const std::string&); //Params are paths to shader files  
            bool loadFromMemory(const std::string&, const std::string&); //Params are the complete loaded shaders

            bool link();
    };
}

#endif //GL_SHADER_PROGRAM_HPP
