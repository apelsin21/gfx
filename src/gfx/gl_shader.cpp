#include "gfx/gl_shader.hpp"

mg::GLShader::GLShader() : Shader() {
    this->id = -1;
	this->vs = -1;
	this->fs = -1;
}
mg::GLShader::~GLShader() {
    if(glIsProgram(this->id) == GL_TRUE) {
        glDeleteProgram(this->id);
    }
}

int mg::GLShader::getAttribLocation(const std::string& name) {
	return glGetAttribLocation(this->id, name.c_str());
}
GLuint mg::GLShader::loadShader(const std::string& p, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType);
	if(glIsShader(shaderID) == GL_FALSE) {
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

	glShaderSource(shaderID, 1, &textPtr, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE) {
	    int errorLogLength = 0;
	    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLogLength);

	    char errorLog[errorLogLength];
	    glGetShaderInfoLog(shaderID, errorLogLength, NULL, &errorLog[0]);
	    printf("GLShader %s failed to compile. Log:\n%s\n", p.c_str(), errorLog);
		return 0;
	}

	return shaderID;
}

bool mg::GLShader::loadFromFile(const std::string& v_path, const std::string& f_path) {
	id = glCreateProgram();
	if(glIsProgram(id) == GL_FALSE) {
		printf("GLShader failed to create GL handle\n");
		return false;
	}

    vs = this->loadShader(v_path, GL_VERTEX_SHADER);
	if(glIsShader(vs) == GL_FALSE) {
		printf("failed to load shader %s\n", v_path.c_str());
        return false;
    }

    fs = this->loadShader(f_path, GL_FRAGMENT_SHADER);
    if(glIsShader(fs) == GL_FALSE) {
		printf("failed to load shader %s\n", f_path.c_str());
        return false;
    }


   	glAttachShader(id, vs);
   	glAttachShader(id, fs);

    glLinkProgram(id);

	GLint result = GL_FALSE;

    glGetProgramiv(id, GL_LINK_STATUS, &result);

	if(result == GL_FALSE) {
        int errorLogLength = 0;
        char errorLog[errorLogLength];

        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errorLogLength);
        glGetProgramInfoLog(id, errorLogLength, NULL, &errorLog[0]);

        printf("GLShader failed to link. Log:\n%s\n", errorLog);
		return false;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

    return true;
}

void mg::GLShader::bindID() {
    if(glIsProgram(id) != GL_FALSE) {
        glUseProgram(id);
    }
}
