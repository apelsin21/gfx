#include "gfx/shader.hpp"

mg::Shader::Shader() {
    _id = -1;
	_vs = -1;
	_fs = -1;

	_loaded = false;
	_linked = false;
}
mg::Shader::~Shader() {
    if(glIsProgram(_id) == GL_TRUE) {
        glDeleteProgram(_id);
    }
}

int mg::Shader::getAttribLocation(const std::string& name) const {
	GLint location = glGetAttribLocation(_id, name.c_str());

	return location;
}
int mg::Shader::getUniformLocation(const std::string& name) const {
	GLint location = glGetUniformLocation(_id, name.c_str());

	return location;
}
GLuint mg::Shader::_loadShader(const std::string& p, GLenum shaderType) {
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
	    printf("Shader %s failed to compile. Log:\n%s\n", p.c_str(), errorLog);
		return 0;
	}

	return shader_id;
}

bool mg::Shader::loadFromFile(const std::string& v_path, const std::string& f_path) {
	_id = glCreateProgram();
	if(glIsProgram(_id) == GL_FALSE) {
		printf("Shader failed to create GL handle\n");
		return false;
	}

    _vs = _loadShader(v_path, GL_VERTEX_SHADER);
	if(glIsShader(_vs) == GL_FALSE) {
		printf("failed to load shader %s\n", v_path.c_str());
        return false;
    }

    _fs = _loadShader(f_path, GL_FRAGMENT_SHADER);
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

        printf("Shader failed to link. Log:\n%s\n", errorLog);
		return false;
	}

	_vsPath = v_path;
	_fsPath = f_path;

	glDeleteShader(_vs);
	glDeleteShader(_fs);

	_loaded = true;
	_linked = true;

    return true;
}

void mg::Shader::bind() const {
    if(glIsProgram(_id) != GL_FALSE) {
        glUseProgram(_id);
    }
}
unsigned int mg::Shader::getGLHandle() const {
	return _id;
}
