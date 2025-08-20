#ifndef UILUAAPI_H
#define UILUAAPI_H

#include <common/Singleton.hpp>
#include <util/lua/Lua.hpp>

namespace UILuaAPI
{
    void registerFunctions(lua_State* L);

    int lua_ui_button_create(lua_State* L);
    int lua_ui_button_destroy(lua_State* L);
}

#endif // UILUAAPI_H
