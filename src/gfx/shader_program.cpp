#include "gfx/shader_program.hpp"

gfx::ShaderProgram::ShaderProgram() {
    this->loaded = false;
    this->linked = false;
    this->id = -1;
}
gfx::ShaderProgram::~ShaderProgram() {
}

void gfx::ShaderProgram::createID() {
    if(!this->hasValidID()) {
        this->id = glCreateProgram();
    }
}
void gfx::ShaderProgram::deleteID() {
    if(this->hasValidID()) {
        glDeleteProgram(this->id);
    }
}
void gfx::ShaderProgram::bindID() {
	if(this->hasValidID()) {
		glUseProgram(this->id);
	}
}
bool gfx::ShaderProgram::hasValidID() {
    if(glIsProgram(this->id) == GL_TRUE) {
        return true;
    } else {
       return false;
    }
}

int gfx::ShaderProgram::getAttribLocation(const std::string& name) {
	return glGetAttribLocation(this->id, name.c_str());
}

bool gfx::ShaderProgram::attachShader(const gfx::Shader& s) {
    if(!this->hasValidID()) {
        std::string errMsg("tried to attach shader ");
        errMsg += s.path;
        errMsg += " of type ";
        errMsg += shaderTypeToString(s.type);
        errMsg += " to shaderprogram with invalid id!\n";
        throw std::runtime_error(errMsg);
        return false;
    }
    
    if(glIsShader(s.id) == GL_FALSE) {
        std::string errMsg("tried to attach shader ");
        errMsg += s.path;
        errMsg += " of type ";
        errMsg += shaderTypeToString(s.type);
        errMsg += " with invalid id, to a shaderprogram!\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    switch(s.type) {
        case SHADER_TYPE::SHADER_TYPE_VERTEX:
	        this->vs = s;
   			glAttachShader(this->id, this->vs.id);
        break;
        case SHADER_TYPE::SHADER_TYPE_FRAGMENT:
        	this->fs = s;
   			glAttachShader(this->id, this->fs.id);
        break;
        default:
            std::string errMsg("tried to attach shader ");
            errMsg += s.path;
            errMsg += " of an unsupported type ";
            errMsg += shaderTypeToString(s.type);
            errMsg += " to shaderprogram!\n";
            throw std::runtime_error(errMsg);
            return false;
        break;
    }

    return true;
}

bool gfx::ShaderProgram::link() {
	if(!this->hasValidID()) {
        throw std::runtime_error("tried to link shaderprogram with invalid id!\n");
		return false;
	}

    glLinkProgram(this->id);
 
	GLint result = GL_FALSE;

    glGetProgramiv(this->id, GL_LINK_STATUS, &result);

	if(result == GL_FALSE) {
        int errorLogLength = 0;
        char errorLog[errorLogLength];

        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &errorLogLength);        
        glGetProgramInfoLog(this->id, errorLogLength, NULL, &errorLog[0]);

        std::string errMsg("shaderprogram failed to link. Log:\n");
        errMsg += errorLog;
        errMsg += "\n";
        throw std::runtime_error(errMsg);
		return false;
	}
 
    return true;
}
