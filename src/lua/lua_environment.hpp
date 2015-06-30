#ifndef LUA_ENVIRONMENT_HPP
#define LUA_ENVIRONMENT_HPP

#include <cstdio>
#include <string>

#include <luajit-2.0/lua.hpp>

namespace mg {
	class LuaEnvironment {
		protected:
			lua_State* L;
		public:
			LuaEnvironment();
			~LuaEnvironment();

			bool registerMetatable(const std::string&, luaL_Reg*);

			bool runScript(const std::string&);
	};
}

#endif //LUA_ENVIRONMENT_HPP
