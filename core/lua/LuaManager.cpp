#include "LuaManager.hpp"

#include <util/Log.hpp>

template<>
LuaManager* Singleton<LuaManager>::instance = nullptr;

LuaManager::LuaManager()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    log_debug("Lua state has been created.");
}

LuaManager::~LuaManager()
{
    log_debug("Closing Lua state...");
    if (L)
    {
        lua_close(L);
    }
    else
    {
        log_warning("Attempt to close Lua state when it is not initialized.");
    }
}

int LuaManager::loadScript(const std::string& scriptPath, const std::string& scriptTableName)
{
    int refID = -1;

    std::string fullScriptPath = scriptDir + scriptPath;

    if (luaL_dofile(L, fullScriptPath.c_str()) != LUA_OK)
    {
        log_error(std::string("Failed to load script from ") + scriptPath);
        log_error(lua_tostring(L, -1));
        lua_pop(L, 1);
        return refID;
    }

    lua_getglobal(L, scriptTableName.c_str());

    if (!lua_istable(L, -1))
    {
        log_error(std::string("Failed to read table name from ") + scriptTableName + std::string(" in the script ") + scriptPath);
        lua_pop(L, 1);
        return refID;
    }

    refID = luaL_ref(L, LUA_REGISTRYINDEX);

    return refID;
}

void LuaManager::callScript(int scriptFunctionTableID, const std::string& runFunctionName, bool callAsMethod, const std::vector<LuaParameter>& args)
{
    if (scriptFunctionTableID == LUA_NOREF)
    {
        log_error(std::string("Invalid scriptFunctionTableID when calling ") + runFunctionName);
        return;
    }

    lua_rawgeti(L, LUA_REGISTRYINDEX, scriptFunctionTableID);

    if (lua_isnil(L, -1))
    {
        log_error(std::string("Nil table reference when calling ") + runFunctionName);
        lua_pop(L, 1);
        return;
    }

    if (!lua_istable(L, -1))
    {
        log_error(std::string("Got not a table when calling ") + runFunctionName);
        lua_pop(L, 1);
        return;
    }

    lua_getfield(L, -1, runFunctionName.c_str());

    if (!lua_isfunction(L, -1))
    {
        log_error(std::string("Unable to find function ") + runFunctionName);
        lua_pop(L, 2); // table loaded successfully so pop 2 elements
        return;
    }

    if (callAsMethod)
    {
        lua_insert(L, -2);
    }

    size_t argsLength = args.size();

    for (const auto& arg : args)
    {
        std::visit([this](auto& value)
        {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, int>) lua_pushnumber(L, value); else
            if constexpr (std::is_same_v<T, double>) lua_pushnumber(L, value); else
            if constexpr (std::is_same_v<T, bool>) lua_pushboolean(L, value); else
            if constexpr (std::is_same_v<T, std::string>) lua_pushstring(L, value.c_str());
        }, arg);
    }

    if (lua_pcall(L, (callAsMethod ? 1 : 0) + argsLength, 0, 0) != LUA_OK)
    {
        log_error(std::string("Unable to call function ") + runFunctionName);
        log_error(lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    return;
}

void LuaManager::unloadScript(int scriptFunctionTableID)
{
    luaL_unref(L, LUA_REGISTRYINDEX, scriptFunctionTableID);
}
