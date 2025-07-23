/* CoreEventManager - the key object in Core event system */

#ifndef COREEVENTMANAGER_HPP
#define COREEVENTMANAGER_HPP

#include <common/EventListener.hpp>
#include <common/EventManager.hpp>

#include "CoreEvent.hpp"
#include "CoreEventTypeGraph.hpp"

class CoreEventManager : public EventManager<CoreEvent, CoreEventTypeGraph>, public Singleton<CoreEventManager>
{
    friend class Singleton<CoreEventManager>;
private:

public:

private:
    CoreEventManager() = default;
    ~CoreEventManager() = default;
};

#endif // COREEVENTMANAGER_HPP
