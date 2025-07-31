#ifndef PARAGONSTATELOADINGSCREEN_HPP
#define PARAGONSTATELOADINGSCREEN_HPP

#include <ParagonApp/scene/ParagonSceneLoadingScreen.hpp>

#include "ParagonState.hpp"

class ParagonStateLoadingScreen : public ParagonState
{
private:
    ParagonSceneLoadingScreen scene;
public:
    ParagonStateLoadingScreen();
    ~ParagonStateLoadingScreen();
    void onEntry() override;
    void onLeave() override;
    const ParagonScene& getScene() const;
};

#endif // PARAGONSTATELOADINGSCREEN_HPP
