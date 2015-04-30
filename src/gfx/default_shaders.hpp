#ifndef DEFAULT_GL_SHADERS_HPP
#define DEFAULT_GL_SHADERS_HPP

#include <string>

namespace gfx {
    #define GLSL(src) "#version 130\n" #src
    
    static const std::string defaultSpriteVertexShader = GLSL(
        in vec2 v_pos;
        in vec2 v_uv;
        in vec3 v_color;

        out vec2 f_uv;
        out vec3 f_color;

        void main(void) {
            f_uv = v_uv;
            f_color = v_color;

            gl_Position = vec4(v_pos.xy, 0.0, 1.0);
        }
    );

    static const std::string defaultSpriteFragmentShader = GLSL(
        in vec2 f_uv;
        in vec3 f_color;

        uniform sampler2D sampler;

        out vec4 out_color;

        void main(void) {
            out_color = texture(sampler, f_uv) * vec4(f_color.xyz, 1.0);
        }
    );
}

#endif //DEFAULT_GL_SHADERS_HPP
