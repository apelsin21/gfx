#include "gfx/gl_shader_program.hpp"

gfx::GLShaderProgram::GLShaderProgram() {
    this->loaded = false;
    this->linked = false;
    this->id = -1;
}
gfx::GLShaderProgram::~GLShaderProgram() {
}

void gfx::GLShaderProgram::createID() {
    if(!this->hasValidID()) {
        this->id = glCreateProgram();
    }
}
void gfx::GLShaderProgram::deleteID() {
    if(this->hasValidID()) {
        glDeleteProgram(this->id);
    }
}
bool gfx::GLShaderProgram::hasValidID() {
    if(glIsProgram(this->id) == GL_TRUE) {
        return true;
    } else {
       return false;
    }
}

bool gfx::GLShaderProgram::attachShader(const gfx::GLShader& s) {
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
            break;
        case SHADER_TYPE::SHADER_TYPE_FRAGMENT:
                this->fs = s;
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

bool gfx::GLShaderProgram::link() {
    return true;
}
