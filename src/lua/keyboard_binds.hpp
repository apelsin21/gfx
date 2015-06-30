#ifndef KEYBOARD_BINDS_HPP
#define KEYBOARD_BINDS_HPP

#include <luajit-2.0/lua.hpp>

#include "core/sdl2_keyboard.hpp"

namespace mg {
	static mg::SDL2Keyboard keyboard;
	static const char* keyboardName = "keyboard";

	int keyboardIsKeyDown(lua_State* L) {
		const char* key = luaL_checkstring(L, 1);

		lua_pushboolean(L, keyboard.isKeyDown(key));

		return 1;
	}

	luaL_Reg keyboardFunctions[] = {
		{"is_key_down", keyboardIsKeyDown},
		{NULL, NULL},
	};
}

#endif //KEYBOARD_BINDS_HPP
