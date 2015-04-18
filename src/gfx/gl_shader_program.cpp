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
       printf("tried to attach shader %s of type %s to shaderprogram with invalid id!\n",
           s.path.c_str(),
           shaderTypeToString(s.type).c_str());
        return false;
    }
    
    if(glIsShader(s.id) == GL_FALSE) {
        printf("tried to attach shader with invalid id %s of type %s to shaderprogram!\n",
            s.path.c_str(),
            shaderTypeToString(s.type).c_str());
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
            printf("tried to attach shader %s of unsupported type %s to shaderprogram!\n",
                s.path.c_str(),
                shaderTypeToString(s.type).c_str());
            return false;
            break;
    }



    return true;
}

bool gfx::GLShaderProgram::link() {
    return true;
}
