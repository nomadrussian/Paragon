#include "EventTypeGraph.hpp"

#include <util/Log.hpp>

#include <cassert>

#include "Singleton.hpp"

void EventTypeGraph::addDependency(std::type_index baseTypeID, std::type_index derivedTypeID)
{
    assert(
        eventPredecessorMap.find(derivedTypeID) == eventPredecessorMap.end() &&
        "Error: trying to add dependency for event type that is already in the eventGraph"
    );

    log_debug(std::string("Adding Event dependency: ") + baseTypeID.name() + " <- " + derivedTypeID.name());
    auto newDependency = std::make_pair(derivedTypeID, baseTypeID);
    eventPredecessorMap.insert(std::pair<std::type_index, std::type_index>(newDependency));
}

bool EventTypeGraph::matchesType(std::type_index matchID, std::type_index typeID)
{
    if(typeID == matchID)
    {
        return true;
    }

    if(eventPredecessorMap.find(typeID) == eventPredecessorMap.end())
    {
        log_warning(typeID.name() + std::string(" has not been found in the event graph"));
        return false;
    }

    while(eventPredecessorMap.find(typeID) != eventPredecessorMap.end())
    {
        typeID = eventPredecessorMap.find(typeID)->second;

        if(typeID == matchID)
        {
            return true;
        }
    }

    return false;
}
