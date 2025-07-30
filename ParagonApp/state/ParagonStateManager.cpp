#include "ParagonStateManager.hpp"

#include <util/Log.hpp>

#include "ParagonStateIntro.hpp"
#include "ParagonStateMainMenu.hpp"
#include "ParagonStateLoadingScreen.hpp"
#include "ParagonStateInWorld.hpp"

ParagonStateManager::ParagonStateManager()
{
    currentState = std::make_unique<ParagonStateIntro>();
}

const std::type_info& ParagonStateManager::getCurrentStateTypeID() const
{
    if (currentState != nullptr)
    {
        const ParagonState& state = *currentState;
        return typeid(state);
    }
    else
    {
        log_warning("Current state in ParagonApplication has not been set!");
        return typeid(ParagonState);
    }
}
