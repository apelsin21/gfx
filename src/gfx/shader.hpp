#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include <stdio.h>
#include <string>
#include <stdexcept>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>

namespace mg {
    class Shader {
		protected:
			GLuint id;
        public:
            GLuint vs, fs;
            bool loaded, linked;

            Shader();
            ~Shader();

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();
            
            bool loadFromFile(const std::string&, const std::string&);

			int getAttribLocation(const std::string&);

            bool link();
    };
}

#endif //GL_SHADER_HPP
