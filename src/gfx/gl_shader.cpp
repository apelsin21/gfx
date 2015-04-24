#include "gfx/gl_shader.hpp"

gfx::GLShader::GLShader() {
    this->id = -1;
    this->type = SHADER_TYPE::SHADER_TYPE_NONE;
}
gfx::GLShader::~GLShader() {
}

GLenum gfx::GLShader::shaderTypeToGLEnum(SHADER_TYPE t) {
    switch(t) {
        case SHADER_TYPE::SHADER_TYPE_VERTEX:
            return GL_VERTEX_SHADER;
            break;             
        case SHADER_TYPE::SHADER_TYPE_FRAGMENT:
            return GL_FRAGMENT_SHADER;
            break;             
        default:
            break;
    }
}

void gfx::GLShader::createID(SHADER_TYPE t) {
    if(glIsShader(this->id) == GL_FALSE) {
        this->type = t;
        this->id = glCreateShader(this->shaderTypeToGLEnum(this->type));
    }
}
void gfx::GLShader::deleteID() {
    if(glIsShader(this->id) == GL_TRUE) {
        glDeleteShader(this->id);
    }
}
bool gfx::GLShader::hasValidID() {
    if(glIsShader(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}

bool gfx::GLShader::loadFromPath(const std::string& p) {
    std::ifstream infile(p, std::ios::in);
    std::string line;

    if(infile.is_open()) {
        this->src = "";
        this->path = p;
        while(std::getline(infile, line)) {
            this->src += line += "\n";
        }

        infile.close();
    } else {
        printf("failed to open shader file %s for reading, insufficient permissions or non-existing file\n", this->path.c_str());
        return false;
    }

    return true;
}
bool gfx::GLShader::loadFromMemory(const std::string& src) {
    this->src = src;

    return true;
}

bool gfx::GLShader::compile() {
    if(!this->hasValidID()) {
        printf("failed to compile invalid GL shader %s, of type %s\n",
            this->path.c_str(),
            shaderTypeToString(this->type).c_str());
        return false;
    }

    GLint result = GL_FALSE;
    const char* textPtr = this->src.c_str();

    glShaderSource(this->id, 1, &textPtr, NULL);
    glCompileShader(this->id);

    glGetShaderiv(this->id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) {
        int errorLogLength = 0;
        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &errorLogLength);        

        char errorLog[errorLogLength];
        glGetShaderInfoLog(this->id, errorLogLength, NULL, &errorLog[0]);

        printf("shader %s of type %s failed to compile. Log:\n%s\n", 
                        this->path.c_str(),
                        shaderTypeToString(this->type).c_str(),
                        errorLog);
    }

    return true;
}