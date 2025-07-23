#include "ParagonEventTypeGraph.hpp"

#include <util/Log.hpp>

template<>
ParagonEventTypeGraph* Singleton<ParagonEventTypeGraph>::instance = nullptr;

ParagonEventTypeGraph::ParagonEventTypeGraph()
{
    // log_debug("Adding ParagonEventTypeGraph dependencies...");
}
