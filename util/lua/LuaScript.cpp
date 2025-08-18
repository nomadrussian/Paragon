#include "LuaScript.hpp"

LuaScript::LuaScript(const std::string& scriptPath, const std::string& scriptTableName)
{
    scriptFunctionTableID = LuaManager::getInstance().loadScript(scriptPath, scriptTableName);
}

LuaScript::~LuaScript()
{
    LuaManager::getInstance().unloadScript(scriptFunctionTableID);
}

void LuaScript::callFunction(const std::string& functionName, bool callAsMethod, const std::vector<LuaParameter>& args)
{
    LuaManager::getInstance().callFunction(scriptFunctionTableID, functionName, callAsMethod, args);
}
