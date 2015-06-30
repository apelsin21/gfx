#include "lua/lua_environment.hpp"
#include "lua/utils.hpp"

int main() {
	mg::LuaEnvironment* env = mg::RegisterMetatables();

	if(!env->runScript("main.lua")) {
		return -1;
	}

	delete env;

	return 0;
}
