#ifndef WINDOW_BINDS_HPP
#define WINDOW_BINDS_HPP

#include <glm/glm.hpp>

#include <luajit-2.0/lua.hpp>

#include "lua/vec2_binds.hpp"

#include "core/sdl2_window.hpp"

namespace mg {
	static mg::SDL2Window window;
	static const char* windowName = "window";

	int windowGetCaption(lua_State* L) {
		lua_pushstring(L, window.getCaption().c_str());

		return 1;
	}
	int windowSetCaption(lua_State* L) {
		const char* c = luaL_checkstring(L, 1);
		window.setCaption(c);

		return 0;
	}

	int windowIsFullscreen(lua_State* L) {
		lua_pushboolean(L, window.isFullscreen());
		return 1;
	}
	int windowIsFocused(lua_State* L) {
		lua_pushboolean(L, window.isFocused());
		return 1;
	}

	int windowGetResolution(lua_State* L) {
		lua_pushnumber(L, window.getResolution().x);
		lua_pushnumber(L, window.getResolution().y);

		vec2New(L);
	}
	int windowSetResolution(lua_State* L) {
		glm::vec2* v = checkVec2(L, 1);

		window.setResolution(*v);

		return 0;
	}
	
	int windowGetPosition(lua_State* L) {
	}
	int windowSetPosition(lua_State* L) {
		glm::vec2* v = checkVec2(L, 1);

		window.setPosition(*v);

		return 0;
	}

	int windowSwapBuffers(lua_State* L) {
		window.swapBuffers();

		return 0;
	}

	luaL_Reg windowFunctions[] = {
		{"get_resolution", windowGetResolution},
		{"set_resolution", windowSetResolution},

		{"get_position", windowGetPosition},
		{"set_position", windowSetPosition},

		{"get_caption", windowGetCaption},
		{"set_caption", windowSetCaption},

		{"is_fullscreen", windowIsFullscreen},
		{"is_focused", windowIsFocused},

		{"swap_buffers", windowSwapBuffers},
		{NULL, NULL},
	};
}

#endif //WINDOW_BINDS_HPP
