#include <stdio.h>
#include <tuple>
#include <exception>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/free_image_texture.hpp"
#include "gfx/free_type_font.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/default_shaders.hpp"
#include "gfx/shader_type.hpp"
#include "gfx/renderer_event.hpp"

int main() {
    gfx::FreeTypeFont font;
    gfx::FreeImageTexture tex;
    gfx::Renderer renderer;
    gfx::Shader vs, fs;
    gfx::ShaderProgram program;

    try {
        renderer.initialize("Test Window", 3, 0, false);

        vs.createID(gfx::SHADER_TYPE::SHADER_TYPE_VERTEX);
        fs.createID(gfx::SHADER_TYPE::SHADER_TYPE_FRAGMENT);
        vs.loadFromMemory(gfx::defaultFontVertexShader);
        fs.loadFromMemory(gfx::defaultFontFragmentShader);
        vs.compile();
        fs.compile();

        program.createID();
        program.attachShader(vs);
        program.attachShader(fs);
        program.link();

        tex.createID();
        tex.loadFromFile("test.png");

		renderer.fontShaderProgram = program;
    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

    GLint vertexShaderPos = glGetAttribLocation(program.id, "v_pos");
    GLint uvShaderPos = glGetAttribLocation(program.id, "v_uv");
    GLint colorShaderPos = glGetAttribLocation(program.id, "v_color");
    GLuint vao, vertex_vbo, uv_vbo, color_vbo;
    glGenBuffers(1, &vertex_vbo);
    glGenBuffers(1, &uv_vbo);
    glGenBuffers(1, &color_vbo);
    glGenVertexArrays(1, &vao);

    static const GLfloat vertices[] = {
        -1.0f, -1.0f, //Bottom left
         1.0f, -1.0f, //Bottom right
        -1.0f,  1.0f, //Top left

         1.0f, -1.0f, //Bottom right
         1.0f,  1.0f, //Top right
        -1.0f,  1.0f, //Top left
    };
    static const GLfloat uvs[] = {
         0.0f,  0.0f, //Bottom left
         1.0f,  0.0f, //Bottom right
         0.0f,  1.0f, //Top left

         1.0f,  0.0f, //Bottom right
         1.0f,  1.0f, //Top right
         0.0f,  1.0f, //Top left
    };
    static const GLfloat colors[] = {
         1.0f,  1.0f, 1.0f, //Bottom left
         1.0f,  1.0f, 1.0f, //Bottom right
         1.0f,  1.0f, 1.0f, //Top left

         1.0f,  1.0f, 1.0f, //Bottom left
         1.0f,  1.0f, 1.0f, //Bottom right
         1.0f,  1.0f, 1.0f, //Top right
    };

    glBindVertexArray(vao);

    // VERTICES
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(vertexShaderPos);
    glVertexAttribPointer(vertexShaderPos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    // UVS
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glEnableVertexAttribArray(uvShaderPos);
    glVertexAttribPointer(uvShaderPos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    // COLORS
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(colorShaderPos);
    glVertexAttribPointer(colorShaderPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    renderer.setClearColor(gfx::Color(0.0f, 1.0f, 1.0f, 1.0f));

    while(renderer.isOpen()) {
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            renderer.close();
            break;
        }

        renderer.begin();
        tex.bindID();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        renderer.end();

        renderer.pollEvents();
        renderer.swapBuffers();
    }

    vs.deleteID();
    fs.deleteID();
    program.deleteID();
    tex.deleteID();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertex_vbo);
    glDeleteBuffers(1, &uv_vbo);
    glDeleteBuffers(1, &color_vbo);

    return EXIT_SUCCESS;
}
