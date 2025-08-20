#ifndef LUAMANAGER_HPP
#define LUAMANAGER_HPP

#include <common/Singleton.hpp>

#include <string>
#include <variant>
#include <vector>

#include "Lua.hpp"

using LuaParameter = std::variant<int, double, bool, std::string>;

class LuaManager : public Singleton<LuaManager>
{
    friend class Singleton<LuaManager>;
    friend class LuaScript;
private:
    lua_State* L;
    const std::string scriptDir = "../scripts/";

protected:
    LuaManager();
    ~LuaManager();

private:
    int loadScript(const std::string& scriptPath, const std::string& scriptTableName); // returns the script table's reference integer
    void callScript(int scriptFunctionTableID, const std::string& runFunctionName, bool callAsMethod, const std::vector<LuaParameter>& args);
    void unloadScript(int scriptFunctionTableID);
};

#endif // LUAMANAGER_HPP
