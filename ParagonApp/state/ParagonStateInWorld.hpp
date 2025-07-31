#ifndef PARAGONSTATEINWORLD_HPP
#define PARAGONSTATEINWORLD_HPP

#include <ParagonApp/scene/ParagonSceneInWorld.hpp>

#include "ParagonState.hpp"

class ParagonStateInWorld : public ParagonState
{
private:
    ParagonSceneInWorld scene;
public:
    ParagonStateInWorld();
    ~ParagonStateInWorld();
    void onEntry();
    void onLeave();
    const ParagonScene& getScene() const;
};

#endif // PARAGONSTATEINWORLD_HPP
