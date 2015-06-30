#include "gfx/shader.hpp"

mg::Shader::Shader() {
    this->loaded = false;
    this->linked = false;

    this->id = -1;
	this->vs = -1;
	this->fs = -1;
}
mg::Shader::~Shader() {
    if(glIsProgram(this->id) == GL_TRUE) {
        glDeleteProgram(this->id);
    }
}

int mg::Shader::getAttribLocation(const std::string& name) {
	return glGetAttribLocation(this->id, name.c_str());
}

bool mg::Shader::loadFromFile(const std::string& v, const std::string& f) {
	id = glCreateProgram();
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::ifstream infile(v, std::ios::in);
	std::string line, src;
	
	if(infile.is_open()) {
	    src = "";
	    while(std::getline(infile, line)) {
	        src += line += "\n";
	    }
	
	    infile.close();
	} else {
	    std::string errMsg("Failed to open vertex shader file ");
	    errMsg += v;
	    errMsg += " for reading, insufficient permissions or non-existing file\n ";
	    throw std::runtime_error(errMsg);
		return false;
	}

	GLint result = GL_FALSE;
	const char* textPtr = src.c_str();
	
	glShaderSource(vs, 1, &textPtr, NULL);
	glCompileShader(vs);
	
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	
	if(result == GL_FALSE) {
	    int errorLogLength = 0;
	    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &errorLogLength);        
	
	    char errorLog[errorLogLength];
	    glGetShaderInfoLog(vs, errorLogLength, NULL, &errorLog[0]);
	
	    std::string errMsg("Vertex shader ");
		errMsg += v;
	    errMsg +=  " failed to compile. Log:\n";
	    errMsg += errorLog;
	    errMsg += "\n";
	    throw std::runtime_error(errMsg);
		return false;
	}

	infile = std::ifstream(f, std::ios::in);
	line = "";
	src = "";
	
	if(infile.is_open()) {
	    src = "";
	    while(std::getline(infile, line)) {
	        src += line += "\n";
	    }
	
	    infile.close();
	} else {
	    std::string errMsg("Failed to open fragment shader file ");
		errMsg += f;
	    errMsg += " for reading, insufficient permissions or non-existing file\n ";
	    throw std::runtime_error(errMsg);
		return false;
	}
	
	result = GL_FALSE;
	textPtr = src.c_str();
	
	glShaderSource(fs, 1, &textPtr, NULL);
	glCompileShader(fs);
	
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	
	if(result == GL_FALSE) {
	    int errorLogLength = 0;
	    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &errorLogLength);        
	
	    char errorLog[errorLogLength];
	    glGetShaderInfoLog(vs, errorLogLength, NULL, &errorLog[0]);
	
	    std::string errMsg("Fragment shader ");
		errMsg += v;
	    errMsg +=  " failed to compile. Log:\n";
	    errMsg += errorLog;
	    errMsg += "\n";
	    throw std::runtime_error(errMsg);
		return false;
	}

   	glAttachShader(id, vs);
   	glAttachShader(id, fs);

    glLinkProgram(id);
 
	result = GL_FALSE;

    glGetProgramiv(id, GL_LINK_STATUS, &result);

	if(result == GL_FALSE) {
        int errorLogLength = 0;
        char errorLog[errorLogLength];

        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errorLogLength);        
        glGetProgramInfoLog(id, errorLogLength, NULL, &errorLog[0]);

        std::string errMsg("Shaderprogram failed to link. Log:\n");
        errMsg += errorLog;
        errMsg += "\n";
        throw std::runtime_error(errMsg);
		return false;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
 
    return true;
}
