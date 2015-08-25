#include "gfx/gl_shader.hpp"

mg::GLShader::GLShader() : Shader() {
    _id = -1;
	_vs = -1;
	_fs = -1;
}
mg::GLShader::~GLShader() {
    if(glIsProgram(_id) == GL_TRUE) {
        glDeleteProgram(_id);
    }
}

int mg::GLShader::getAttribLocation(const std::string& name) const {
	GLint location = glGetAttribLocation(_id, name.c_str());

	if(location == -1) {
		printf("Failed to find shader attribute %s in shader %s.\n", name.c_str(), _vsPath.c_str());
	}
	
	return location;
}
int mg::GLShader::getUniformLocation(const std::string& name) const {
	GLint location = glGetUniformLocation(_id, name.c_str());

	if(location == -1) {
		printf("Failed to find shader uniform %s in shader %s.\n", name.c_str(), _vsPath.c_str());
	}

	return location;
}
GLuint mg::GLShader::loadShader(const std::string& p, GLenum shaderType) {
	GLuint shader_id = glCreateShader(shaderType);
	if(glIsShader(shader_id) == GL_FALSE) {
		printf("Failed to create GL handle for shader %s\n", p.c_str());
		return 0;
	}

	std::ifstream infile(p, std::ios::in);
	std::string line, src;

	if(infile.is_open()) {
	    src = "";
	    while(std::getline(infile, line)) {
	        src += line += "\n";
	    }

	    infile.close();
	} else {
	    printf("Failed to open shader %s for reading, insufficient permissions or non-existing file.\n", p.c_str());
		return 0;
	}

	GLint result = GL_FALSE;
	const char* textPtr = src.c_str();

	glShaderSource(shader_id, 1, &textPtr, NULL);
	glCompileShader(shader_id);

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE) {
	    int errorLogLength = 0;
	    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &errorLogLength);

	    char errorLog[errorLogLength];
	    glGetShaderInfoLog(shader_id, errorLogLength, NULL, &errorLog[0]);
	    printf("GLShader %s failed to compile. Log:\n%s\n", p.c_str(), errorLog);
		return 0;
	}

	return shader_id;
}

bool mg::GLShader::loadFromFile(const std::string& v_path, const std::string& f_path) {
	_id = glCreateProgram();
	if(glIsProgram(_id) == GL_FALSE) {
		printf("GLShader failed to create GL handle\n");
		return false;
	}

    _vs = this->loadShader(v_path, GL_VERTEX_SHADER);
	if(glIsShader(_vs) == GL_FALSE) {
		printf("failed to load shader %s\n", v_path.c_str());
        return false;
    }

    _fs = this->loadShader(f_path, GL_FRAGMENT_SHADER);
    if(glIsShader(_fs) == GL_FALSE) {
		printf("failed to load shader %s\n", f_path.c_str());
        return false;
    }


   	glAttachShader(_id, _vs);
   	glAttachShader(_id, _fs);

    glLinkProgram(_id);

	GLint result = GL_FALSE;

    glGetProgramiv(_id, GL_LINK_STATUS, &result);

	if(result == GL_FALSE) {
        int errorLogLength = 0;
        char errorLog[errorLogLength];

        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &errorLogLength);
        glGetProgramInfoLog(_id, errorLogLength, NULL, &errorLog[0]);

        printf("GLShader failed to link. Log:\n%s\n", errorLog);
		return false;
	}

	_vsPath = v_path;
	_fsPath = f_path;

	glDeleteShader(_vs);
	glDeleteShader(_fs);

    return true;
}

void mg::GLShader::bind() const {
    if(glIsProgram(_id) != GL_FALSE) {
        glUseProgram(_id);
    }
}
unsigned int mg::GLShader::getGLHandle() const {
	return _id;
}
