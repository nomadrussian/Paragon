#ifndef PARAGONSTATEMAINMENU_HPP
#define PARAGONSTATEMAINMENU_HPP

#include <ParagonApp/scene/ParagonSceneMainMenu.hpp>

#include "ParagonState.hpp"

class ParagonStateMainMenu : public ParagonState
{
private:
    ParagonSceneMainMenu scene;
public:
    ParagonStateMainMenu();
    ~ParagonStateMainMenu();
    void onEntry();
    void onLeave();
    const ParagonScene& getScene() const;
};

#endif // PARAGONSTATEMAINMENU_HPP
