#ifndef LUA_HPP
#define LUA_HPP

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

using lua_CFunction = int(*)(lua_State* L);

#endif // LUA_HPP
