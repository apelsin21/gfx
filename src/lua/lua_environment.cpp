#include "lua/lua_environment.hpp"

mg::LuaEnvironment::LuaEnvironment() {
	L = luaL_newstate();
	luaL_openlibs(L);
}
mg::LuaEnvironment::~LuaEnvironment() {
	if(L != nullptr) {
		lua_close(L);
	}
}

bool mg::LuaEnvironment::registerMetatable(const std::string& s, luaL_Reg* functions) {
	if(luaL_newmetatable(L, s.c_str()) == 0) {
		printf("Error registring Lua metatable %s, a metatable with that name already exists!\n", s.c_str());
	}
	luaL_register(L, NULL, functions);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	lua_setglobal(L, s.c_str());

	return true;
}

bool mg::LuaEnvironment::runScript(const std::string& path) {
	int error = luaL_dofile(L, path.c_str());

	if(error) {
		printf("Error in Lua script %s:\n %s\n", path.c_str(), lua_tostring(L, -1));
		lua_pop(L, 1);
		return false;
	}

	return true;
}
