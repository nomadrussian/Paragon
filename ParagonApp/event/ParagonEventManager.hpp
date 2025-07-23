#ifndef PARAGONEVENTMANAGER_HPP
#define PARAGONEVENTMANAGER_HPP

#include <common/EventManager.hpp>
#include <common/Singleton.hpp>

#include "ParagonEvent.hpp"
#include "ParagonEventTypeGraph.hpp"

class ParagonEventManager : public EventManager<ParagonEvent, ParagonEventTypeGraph>, public Singleton<ParagonEventManager>
{
    friend class Singleton<ParagonEventManager>;
protected:
    ParagonEventManager() = default;
    ~ParagonEventManager() = default;
};

#endif // PARAGONEVENTMANAGER_HPP
