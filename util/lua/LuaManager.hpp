#ifndef LUAMANAGER_HPP
#define LUAMANAGER_HPP

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <common/Singleton.hpp>

#include <string>
#include <variant>
#include <vector>

using LuaParameter = std::variant<int, double, bool, std::string>;

class LuaManager : public Singleton<LuaManager>
{
    friend class Singleton<LuaManager>;
    friend class LuaScript;
private:
    lua_State* L;

protected:
    LuaManager();
    ~LuaManager();

private:
    int loadScript(const std::string& scriptPath, const std::string& scriptTableName); // returns the script table's reference integer
    void callFunction(int scriptFunctionTableID, const std::string& functionName, bool callAsMethod, const std::vector<LuaParameter>& args);
    void unloadScript(int scriptFunctionTableID);
};

#endif // LUAMANAGER_HPP
