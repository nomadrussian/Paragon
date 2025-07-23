#include "ParagonApplication.hpp"

#include <util/Log.hpp>

#include "event/ParagonEventManager.hpp"

ParagonApplication::ParagonApplication()
{
}

void ParagonApplication::init()
{
    log_debug("Initializing ParagonEventManager...");
    ParagonEventManager::init();

    log_debug("ParagonScene has been created");
}

ApplicationType ParagonApplication::getApplicationType() const
{
    return PARAGON;
}

void ParagonApplication::update()
{

}
