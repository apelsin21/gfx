#ifndef SDL2_KEYS_HPP
#define SDL2_KEYS_HPP

#include <SDL2/SDL.h>

#include "gfx/keyboardkeys.hpp"

namespace gfx {
    //a function that specifically converts a KEYBOARD_KEY to a SDL_Scancode, and returns the result.
    //if no direct match is available, result is SDL_SCANCODE_UNKNOWN.
    SDL_Scancode convertKeyToSDLScancode(gfx::KEYBOARD_KEY gfxKey);
}

#endif //SDL2_KEYS_HPP
