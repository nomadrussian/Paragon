#include "ParagonApplication.hpp"

#include <core/Core.hpp>
#include <core/render/RenderHandler.hpp>
#include <util/Debugger.hpp>
#include <util/Log.hpp>

#include "config/ParagonConfig.hpp"
#include "event/ParagonEventManager.hpp"
#include "state/ParagonState.hpp"
#include "state/ParagonStateIntro.hpp"

#include <string>

ParagonApplication::ParagonApplication()
{
}

void ParagonApplication::init()
{
    log_debug("Initializing ParagonEventManager...");
    ParagonEventManager::init();

    log_debug("Initializing ParagonStateManager...");
    stateManager = std::make_unique<ParagonStateManager>();

    log_debug("ParagonApplication has been initialized");
}

void ParagonApplication::update()
{
    if (Core::getInstance().getDeltaTime() >= 1.0f / ParagonConfig::TICKRATE)
    {
        ParagonEventManager::getInstance().flushEvents();
    }
}

ApplicationType ParagonApplication::getApplicationType() const
{
    return ApplicationType::PARAGON;
}

const ApplicationScene& ParagonApplication::getCurrentScene() const
{
    return stateManager->getCurrentScene();
}
