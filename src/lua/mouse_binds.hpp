#ifndef MOUSE_BINDS_HPP
#define MOUSE_BINDS_HPP

#include <luajit-2.0/lua.hpp>

#include "lua/vec2_binds.hpp"

#include "core/sdl2_mouse.hpp"

namespace mg {
	static mg::SDL2Mouse mouse;
	static const char* mouseName = "mouse";

	int mouseGetPosition(lua_State* L) {
		lua_pushnumber(L, mouse.getPosition().x);
		lua_pushnumber(L, mouse.getPosition().y);

		return vec2New(L);
	}
	
	int mouseIsLeftButtonDown(lua_State* L) {
		lua_pushboolean(L, mouse.isLeftButtonDown());

		return 1;
	}
	int mouseIsMiddleButtonDown(lua_State* L) {
		lua_pushboolean(L, mouse.isMiddleButtonDown());

		return 1;
	}
	int mouseIsRightButtonDown(lua_State* L) {
		lua_pushboolean(L, mouse.isRightButtonDown());

		return 1;
	}

	luaL_Reg mouseFunctions[] = {
		{"get_position", mouseGetPosition},

		{"is_left_button_down", mouseIsLeftButtonDown},
		{"is_middle_button_down", mouseIsMiddleButtonDown},
		{"is_right_button_down", mouseIsRightButtonDown},

		{NULL, NULL},
	};
}

#endif //MOUSE_BINDS_HPP
