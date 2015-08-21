#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include <string>

#include <epoxy/gl.h>

#include "gfx/shader.hpp"

namespace mg {
    class GLShader : public Shader {
		protected:
		    GLuint loadShader(const std::string&, GLenum);
			GLuint _id, _vs, _fs;

			std::string _vsPath, _fsPath;
        public:
            GLShader();
            ~GLShader();

			void createID();
			void deleteID();
			void bind() const;
			unsigned int getGLHandle() const;
			bool hasValidID();

            bool loadFromFile(const std::string&, const std::string&);

			int getAttribLocation(const std::string&) const;
			int getUniformLocation(const std::string&) const;

            bool link();
    };
}

#endif //GL_SHADER_HPP
