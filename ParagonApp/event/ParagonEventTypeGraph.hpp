#ifndef COREEVENTTYPEGRAPH_HPP
#define COREEVENTTYPEGRAPH_HPP

#include <common/EventTypeGraph.hpp>
#include <common/Singleton.hpp>

class ParagonEventTypeGraph : public EventTypeGraph, public Singleton<ParagonEventTypeGraph>
{
    friend class Singleton<ParagonEventTypeGraph>;
protected:
    ParagonEventTypeGraph();
    ~ParagonEventTypeGraph() = default;
};

#endif // COREEVENTTYPEGRAPH_HPP
