#ifndef SDL2_KEYS_HPP
#define SDL2_KEYS_HPP

#include <SDL2/SDL.h>

#include "gfx/keyboardkeys.hpp"

namespace gfx {
    SDL_Scancode convertKeyToSDLScancode(gfx::KEYBOARD_KEY gfxKey);
}

#endif //SDL2_KEYS_HPP
