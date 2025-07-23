#ifndef COREEVENTTYPEGRAPH_HPP
#define COREEVENTTYPEGRAPH_HPP

#include <common/EventTypeGraph.hpp>
#include <common/Singleton.hpp>

class CoreEventTypeGraph : public EventTypeGraph, public Singleton<CoreEventTypeGraph>
{
    friend class Singleton<CoreEventTypeGraph>;
protected:
    CoreEventTypeGraph();
    ~CoreEventTypeGraph() = default;
};

#endif // COREEVENTTYPEGRAPH_HPP
