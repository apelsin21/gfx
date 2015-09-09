#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>

#include <epoxy/gl.h>

namespace mg {
    class Shader {
		protected:
		    GLuint _loadShader(const std::string&, GLenum);
			GLuint _id, _vs, _fs;
            bool _loaded, _linked;

			std::string _vsPath, _fsPath;
        public:
            Shader();
            ~Shader();

			void createID();
			void deleteID();
			void bind() const;
			unsigned int getGLHandle() const;
			bool hasValidID();

            bool loadFromFile(const std::string&, const std::string&);
			bool isLoaded();

			int getAttribLocation(const std::string&) const;
			int getUniformLocation(const std::string&) const;

            bool link();
			bool isLinked();
    };
}

#endif //SHADER_HPP
