#ifndef PARAGONCHANGESTATEEVENT_HPP
#define PARAGONCHANGESTATEEVENT_HPP

#include <ParagonApp/state/ParagonState.hpp>

#include <typeindex>

#include "ParagonEvent.hpp"

class ParagonStateEvent : public ParagonEvent
{
public:
    const std::type_index& headingTo;
    ParagonStateEvent(const std::type_index& headingTo) : headingTo(headingTo) {}
};

#endif // PARAGONCHANGESTATEEVENT_HPP
