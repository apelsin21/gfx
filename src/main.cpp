#include <stdio.h>
#include <tuple>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/free_image_texture.hpp"
#include "gfx/free_type_font.hpp"
#include "gfx/gl_renderer.hpp"
#include "gfx/gl_shader.hpp"
#include "gfx/gl_shader_program.hpp"
#include "gfx/default_gl_shaders.hpp"
#include "gfx/shader_type.hpp"
#include "gfx/renderer_event.hpp"

int main() {
    //Constructors are memory safe, so no exception can happen here
    gfx::GLRenderer renderer; //"Modern" OpenGL Renderer
    gfx::GLShader vs; //Vertex Shader
    gfx::GLShader fs; //Fragment Shader
    gfx::GLShaderProgram program; //A shader program using the aforementioned shaders
    gfx::FreeTypeFont font; //A font using FreeType2 to load and cache text, load offsets, etc
   
    //A lot of things have runtime exceptions
    try {
        renderer.initialize("Window", 3, 0, false); //Initializes specific GL version, creates SDL2 window. Fails if the requested GL version is unavailable

        vs.createID(gfx::SHADER_TYPE::SHADER_TYPE_VERTEX); //Fails if invalid GL context
        fs.createID(gfx::SHADER_TYPE::SHADER_TYPE_FRAGMENT);

        vs.loadFromMemory(gfx::defaultFontVertexShader); //Loads a predifined shader from memory 
        fs.loadFromMemory(gfx::defaultFontFragmentShader);

        vs.compile(); //Failes if there are errors in the shader
        fs.compile();

        program.createID();

        program.attachShader(vs); //Fails if the shader param is invalid
        program.attachShader(fs);

        program.link();

        font.loadFromFile("data/fonts/FreeSans.ttf", 12); //Can fail for the typical reasons
    } catch(std::runtimeexception(e) {
        printf("error msg: %s\n", e.msg());
        return EXIT_FAILURE;
    }

    while(renderer.isOpen()) {
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            renderer.close();
        }
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_F11)) {
            renderer.setFullscreen(!renderer.getFullscreen()); //Switches between fullscreen and windowed mode on F11 keypress
        }

        renderer.begin(); //Clears the backbuffer
        renderer.end(); //Resets state for next draw call

        renderer.pollEvents(); //Events like if resolution changed, resizing of the window, close event, etc. Unhandled for now
        renderer.swapBuffers(); //Presents the backbuffer to the window
    }

    vs.deleteID(); //Cannot be handled in the destructor since they would happen silently if we passed the object as a parameter, must be manual
    fs.deleteID();
    program.deleteID();
    
    return EXIT_SUCCESS;
}
