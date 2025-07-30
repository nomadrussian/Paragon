/* EventManager - base class for all EventManagers */

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <util/Log.hpp>

#include <algorithm>
#include <cassert>
#include <memory>
#include <queue>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "Event.hpp"
#include "EventListener.hpp"
#include "EventTypeGraph.hpp"

template <typename BaseEventType, typename EventTypeGraphName>
class EventManager
{
private:
    std::unordered_map<std::type_index, std::vector<std::shared_ptr<EventListener>>> inputEventListenersMap;
    std::queue<std::shared_ptr<Event>> eventQueue;

public:
    virtual ~EventManager() = default;

    template <typename EventType>
    void subscribe(const std::shared_ptr<EventListener> listener)
    {
        static_assert(std::is_base_of<BaseEventType, EventType>::value, "Trying to subscribe to non-BaseEventType");
        const std::type_index eventTypeID = typeid(EventType);
        auto& list = inputEventListenersMap[eventTypeID];

        if (std::find(list.begin(), list.end(), listener) == list.end())
        {
            inputEventListenersMap[eventTypeID].push_back(listener);
        } else {
            const EventListener& r_listener = *listener;
            log_warning(
                typeid(*this).name() + std::string(": ") +
                typeid(r_listener).name() + std::string(" attempts to subscribe to the event ") +
                typeid(EventType).name() + std::string(" but it has already subscribed")
            );
        }
    }

    void postEvent(std::shared_ptr<Event> event)
    {
        Event& r_event = *event;
        // using separate methods to check root event type and then actual event type seems redundant
        if(event->matchesType<BaseEventType>())
        {
            eventQueue.push(event);
        } else {
            log_warning(typeid(*this).name() + std::string(" cannot handle events of type ") + typeid(r_event).name());
        }
    }

    void flushEvents()
    {
        while (!eventQueue.empty())
        {
            const auto& event = eventQueue.front();

            const Event& r_event = *event;
            const std::type_index eventTypeID = typeid(r_event);

            for(const auto& list: inputEventListenersMap)
            {
                if(EventTypeGraphName::getInstance().matchesType(list.first, eventTypeID))
                {
                    for(auto listener: list.second)
                    {
                        listener->onEvent(r_event);
                    }
                }
            }

            eventQueue.pop();
        }
    }

protected:
    EventManager() = default;
};

#endif // EVENTMANAGER_HPP
