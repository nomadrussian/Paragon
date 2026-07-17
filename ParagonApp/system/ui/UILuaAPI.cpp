#include "UILuaAPI.hpp"

#include <glm/glm.hpp>

#include "UIComponent.hpp"
#include "UIEntity.hpp"
#include "UIEntityManager.hpp"

/*
 * Lua has to pass all parameters as a table, e.g.
 * ui_function({
 *     x = 128,
 *     y = 256,
 *     text = "PLACEHOLDER"
 * })
 */
namespace UILuaAPI
{
    const std::string api_error = "UILuaAPI error: ";

    void registerFunctions(lua_State* L)
    {
        lua_newtable(L);

        lua_pushcfunction(L, lua_ui_button_create);
        lua_setfield(L, -2, "button_create");
        lua_pushcfunction(L, lua_ui_button_destroy);
        lua_setfield(L, -2, "destroy");

        lua_setglobal(L, "ui");
    }

    /*
     * @parameter1: availableToUse (boolean)
     * @parameter2: script (string)
     * @parameter3: x (number)
     * @parameter4: y (number)
     * @parameter5: width (number)
     * @parameter6: height (number)
     * @parameter7: textlabel (string)
     * @parameter8: texture (number)
     */
    int lua_ui_button_create(lua_State* L)
    {
        glm::vec2 transfromVector = {
            static_cast<GLfloat>(luaL_checknumber(L, 1)),
            static_cast<GLfloat>(luaL_checknumber(L, 2))
        };

        glm::vec2 rectangleDimensions = {
            static_cast<GLfloat>(luaL_checknumber(L, 3)),
            static_cast<GLfloat>(luaL_checknumber(L, 4))
        };

        UIRectangleComponent* pUIRectangleComponent;
        UITransform2DComponent* pUITransform2DComponent;
        UIClickComponent* pUIClickComponent;
        UITextComponent* pUITextComponent;

        UIEntityID newButton = UIEntityManager::getInstance().createNewEntity();
        if (pUIRectangleComponent != UIEntityManager::getInstance().addComponent<UIRectangleComponent>(newButton))
        {
            //log_error(std::string())
        }
        UIEntityManager::getInstance().addComponent<UITransform2DComponent>(newButton);
        UIEntityManager::getInstance().addComponent<UIClickComponent>(newButton);
        UIEntityManager::getInstance().addComponent<UIHoverableComponent>(newButton);
        UIEntityManager::getInstance().addComponent<UITextComponent>(newButton);

        lua_pushinteger(L, newButton);
        return 1;
    }

    int lua_ui_button_destroy(lua_State* L)
    {
        return 1;
    }

    int lua_ui_destroy(lua_State* L)
    {
        return 0;
    }

    namespace
    {
        //float getMandatoryFloat(lua_State* L, int tableIndex, )
    }
}
