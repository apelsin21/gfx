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
#include "gfx/gl_object.hpp"

namespace mg {
    class Shader : public GLObject {
        public:
            std::string src, path;
            SHADER_TYPE type;
            
            Shader();
            ~Shader();

            void createID(SHADER_TYPE);
            void deleteID();
            bool hasValidID();

            bool loadFromFile(const std::string&);
            bool loadFromMemory(const std::string&);

            bool compile();            
    };
}

#endif //GL_SHADER_HPP
