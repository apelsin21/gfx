#ifndef GL_SHADER_PROGRAM_HPP
#define GL_SHADER_PROGRAM_HPP

#include <stdio.h>
#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

#include "gfx/shader.hpp"
#include "gfx/gl_object.hpp"

namespace gfx {
    class ShaderProgram : public GLObject {
        public:
            gfx::Shader vs, fs, geom, tess;
            bool loaded, linked;

            ShaderProgram();
            ~ShaderProgram();

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();
            
            bool attachShader(const Shader&);

            bool loadFromPaths(const std::string&, const std::string&);
            bool loadFromMemory(const std::string&, const std::string&);

			int getAttribLocation(const std::string&);

            bool link();
    };
}

#endif //GL_SHADER_PROGRAM_HPP
