#ifndef VEC2_BINDS_HPP
#define VEC2_BINDS_HPP

#include <glm/glm.hpp>

#include <luajit-2.0/lua.hpp>

namespace mg {
	static const char* vec2Name = "vec2";
	
	glm::vec2* checkVec2(lua_State* L, int n) {
	    return *(glm::vec2**)luaL_checkudata(L, n, vec2Name);
	}
	
	int vec2New(lua_State* L) {
	    unsigned int num_args = lua_gettop(L);
	
	    glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
	    
	    if(num_args == 2) {
	        float x = lua_tonumber(L, 1);
	        float y = lua_tonumber(L, 2);
	
	        *vec = new glm::vec2(x, y);
	    } else {
	        *vec = new glm::vec2();
	    }
	
	    luaL_getmetatable(L, vec2Name);
	    lua_setmetatable(L, -2);
	
	    return 1;
	}
	int vec2GC(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	
	    delete vec;
	
	    return 0;
	}
	
	int vec2SetX(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	
	    vec->x = luaL_checknumber(L, 2);
	
	    return 0;
	}
	int vec2SetY(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	
	    vec->y = luaL_checknumber(L, 2);
	
	    return 0;
	}
	int vec2SetXY(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	
	    vec->x = luaL_checknumber(L, 2);
	    vec->y = luaL_checknumber(L, 3);
	
	    return 0;
	}
	
	int vec2GetX(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	
	    lua_pushnumber(L, vec->x);
	
	    return 1;
	}
	int vec2GetY(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	
	    lua_pushnumber(L, vec->y);
	
	    return 1;
	}
	
	int vec2Normalize(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	
	    vec->x = glm::normalize(vec->x);
	    vec->y = glm::normalize(vec->y);
	
	    return 0;
	}
	
	int vec2Concat(lua_State* L) {
	    std::string stringarg(luaL_checkstring(L, 1));
	    glm::vec2* vecarg = checkVec2(L, 2);
	
	    stringarg += std::to_string(vecarg->x);
	    stringarg += "x";
	    stringarg += std::to_string(vecarg->y);
	
	    lua_pushstring(L, stringarg.c_str());
	
	    return 1;
	}
	
	int vec2Equal(lua_State* L) {
	    glm::vec2* lvec = checkVec2(L, 1);
	    glm::vec2* rvec = checkVec2(L, 2);
	
	    lua_pushboolean(L, *lvec == *rvec);
	    
	    return 1;
	}
	
	int vec2Add(lua_State* L) {
	    glm::vec2* lvec = checkVec2(L, 1);
	    int rtype = lua_type(L, 2);
	
	    switch(rtype) {
	        case LUA_TNUMBER: {
	            float rnumber = luaL_checknumber(L, 2);
	            
	            glm::vec2** numbervec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
	            *numbervec = new glm::vec2(*lvec + rnumber);
	
	            luaL_getmetatable(L, vec2Name);
	            lua_setmetatable(L, -2);
	           
	            return 1;
	
	            break;
	                          }
	        case LUA_TUSERDATA: {
	            glm::vec2* rvec = checkVec2(L, 2);
	            glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
	            *vec = new glm::vec2(*lvec + *rvec);
	
	            luaL_getmetatable(L, vec2Name);
	            lua_setmetatable(L, -2);
	                
	            return 1;
	
	            break;
	                            }
	        default:
	            luaL_error(L, "vec2 __add right arg not number or userdata");
	
	            return 0;
	            break;
	    }
	}
	int vec2Multiplication(lua_State* L) {
	    glm::vec2* lvec = checkVec2(L, 1);
	    int rtype = lua_type(L, 2);
	
	    switch(rtype) {
	        case LUA_TNUMBER: {
	            float rnumber = luaL_checknumber(L, 2);
	            
	            glm::vec2** numbervec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
	            *numbervec = new glm::vec2(*lvec * rnumber);
	
	            luaL_getmetatable(L, vec2Name);
	            lua_setmetatable(L, -2);
	           
	            return 1;
	
	            break;
	                          }
	        case LUA_TUSERDATA: {
	            glm::vec2* rvec = checkVec2(L, 2);
	            glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
	            *vec = new glm::vec2(*lvec * *rvec);
	
	            luaL_getmetatable(L, vec2Name);
	            lua_setmetatable(L, -2);
	                
	            return 1;
	
	            break;
	                            }
	        default:
	            luaL_error(L, "vec2 __mul right arg not number or userdata");
	
	            return 0;
	            break;
	    }
	}
	
	int vec2Clamp(lua_State* L) {
	    glm::vec2* vec = checkVec2(L, 1);
	    
	    float min = luaL_checknumber(L, 2);
	    float max = luaL_checknumber(L, 3);
	
	    vec->x = glm::clamp(vec->x, min, max);
	    vec->y = glm::clamp(vec->y, min, max);
	
	    return 0;
	}
	
	luaL_Reg vec2Functions[] = {
	    {"new", vec2New},
	
	    {"set_x", vec2SetX},
	    {"set_y", vec2SetY},
	    {"set_xy", vec2SetXY},
	
	    {"get_x", vec2GetX},
	    {"get_y", vec2GetY},
	
	    {"normalize", vec2Normalize},
	    {"clamp", vec2Clamp},
	
	    {"__mul", vec2Multiplication},
	    {"__add", vec2Add},
	    {"__concat", vec2Concat},
	    {"__eq", vec2Equal},
	    {"__gc", vec2GC},
	    {NULL, NULL}
	};
}

#endif //VEC2_BINDS_HPP
