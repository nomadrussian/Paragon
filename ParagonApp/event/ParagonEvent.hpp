#ifndef PARAGONEVENT_HPP
#define PARAGONEVENT_HPP

#include <common/Event.hpp>

class ParagonEvent : public Event
{
public:
    virtual ~ParagonEvent() = default;
protected:
    ParagonEvent() = default;
};

#endif // PARAGONEVENT_HPP
