#ifndef UTILS_HPP
#define UTILS_HPP

#include "lua/lua_environment.hpp"
#include "lua/window_binds.hpp"
#include "lua/vec2_binds.hpp"
#include "lua/keyboard_binds.hpp"
#include "lua/mouse_binds.hpp"

namespace mg {
	mg::LuaEnvironment* RegisterMetatables() {
		mg::LuaEnvironment* env = new mg::LuaEnvironment();

		if(!env->registerMetatable(mg::windowName, mg::windowFunctions)) {
			return nullptr;
		}
		if(!env->registerMetatable(mg::vec2Name, mg::vec2Functions)) {
			return nullptr;
		}
		if(!env->registerMetatable(mg::keyboardName, mg::keyboardFunctions)) {
			return nullptr;
		}
		if(!env->registerMetatable(mg::mouseName, mg::mouseFunctions)) {
			return nullptr;
		}

		return env;
	}
}

#endif //UTILS_HPP
