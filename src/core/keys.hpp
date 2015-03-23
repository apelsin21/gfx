#ifndef KEYS_HPP
#define KEYS_HPP

#include <SDL2/SDL.h>

#include "core/keyboardkeys.hpp"

namespace core {
    //a function that specifically converts a KEYBOARD_KEY to a SDL_Scancode, and returns the result.
    //if no direct match is available, result is SDL_SCANCODE_UNKNOWN.
    SDL_Scancode convertKeyToSDLScancode(core::KEYBOARD_KEY gfxKey);
}

#endif //KEYS_HPP
