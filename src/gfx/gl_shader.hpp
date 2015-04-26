#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include <GL/glew.h>

#include "gfx/shader_type.hpp"

namespace gfx {
    class GLShader {
        protected:
            GLenum shaderTypeToGLEnum(SHADER_TYPE);
        public:
            unsigned int id;
            std::string src, path;
            SHADER_TYPE type;
            
            GLShader();
            ~GLShader();

            void createID(SHADER_TYPE);
            void deleteID();
            bool hasValidID();

            bool loadFromPath(const std::string&);
            bool loadFromMemory(const std::string&);

            bool compile();            
    };
}

#endif //GL_SHADER_HPP
