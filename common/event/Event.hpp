#ifndef EVENT_HPP
#define EVENT_HPP

#include <typeinfo>

class Event
{
public:
    template <typename EventT>
    bool matchesType() const
    {
        return dynamic_cast<const EventT*>(this) != nullptr;
    }

    template <typename EventT>
    bool matchesExactType() const
    {
        return typeid(*this) == typeid(EventT);
    }

    virtual ~Event() = default;
protected:
    Event() = default;
};

#endif // EVENT_HPP
