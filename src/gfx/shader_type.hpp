#ifndef SHADER_TYPE_HPP
#define SHADER_TYPE_HPP

namespace gfx {
    enum SHADER_TYPE {
        SHADER_TYPE_NONE,
        
        //OPENGL
        SHADER_TYPE_VERTEX,
        SHADER_TYPE_FRAGMENT,
        SHADER_TYPE_GEOMETRY,
        SHADER_TYPE_TESSELATION,
    };

    static std::string shaderTypeToString(SHADER_TYPE t) {
        std::string returnStr = "SHADER_TYPE_";
        switch(t) {
            case SHADER_TYPE_VERTEX:
                returnStr += "VERTEX";
                break;
            case SHADER_TYPE_FRAGMENT:
                returnStr += "FRAGMENT";
                break;
            case SHADER_TYPE_GEOMETRY:
                returnStr += "GEOMETRY";
                break;
            case SHADER_TYPE_TESSELATION:
                returnStr += "TESSELATION";
                break;
            default:
                returnStr += "NONE";
                break;
        }

        return returnStr;
    }
}

#endif //SHADER_TYPE_HPP
