#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

#include <memory>

#include "Event.hpp"

class EventListener : public std::enable_shared_from_this<EventListener>
{
public:
    virtual void init() = 0;
    virtual void onEvent(const Event& event) = 0;
    virtual ~EventListener() = default;
protected:
    EventListener() = default;
};

#endif // EVENTLISTENER_HPP
