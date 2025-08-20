#include "LuaScript.hpp"

LuaScript::LuaScript(const std::string& scriptPath, const std::string& scriptTableName)
{
    scriptFunctionTableID = LuaManager::getInstance().loadScript(scriptPath, scriptTableName);
}

LuaScript::~LuaScript()
{
    LuaManager::getInstance().unloadScript(scriptFunctionTableID);
}

void LuaScript::callScript(const std::string& runFunctionName, bool callAsMethod, const std::vector<LuaParameter>& args)
{
    LuaManager::getInstance().callScript(scriptFunctionTableID, runFunctionName, callAsMethod, args);
}
