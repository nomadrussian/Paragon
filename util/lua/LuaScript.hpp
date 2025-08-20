#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include "LuaManager.hpp"

#include <string>
#include <vector>

class LuaScript
{
private:
    int scriptFunctionTableID;

public:
    LuaScript(const std::string& scriptPath, const std::string& scriptTableName);
    ~LuaScript();
    void callScript(const std::string& runFunctionName, bool callAsMethod, const std::vector<LuaParameter>& args);
};

#endif // LUASCRIPT_HPP
