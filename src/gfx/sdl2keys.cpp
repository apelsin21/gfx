#include "gfx/sdl2keys.hpp"

SDL_Scancode gfx::convertKeyToSDLScancode(gfx::KEYBOARD_KEY gfxKey) {
    SDL_Scancode sdlKey = SDL_SCANCODE_UNKNOWN;

    switch(gfxKey) {
        case gfx::KEYBOARD_KEY::KEY_ESCAPE:
            sdlKey = SDL_SCANCODE_ESCAPE;
            break;
        default:
            break;
    }

    return sdlKey;
}
