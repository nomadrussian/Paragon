/* CoreEvent - base class for all the events which are specific for the Core */

#ifndef COREEVENT_HPP
#define COREEVENT_HPP

#include <common/Event.hpp>

class CoreEvent : public Event
{
protected:
    CoreEvent() = default;
};

#endif // COREEVENT_HPP
