/* EventTypeGraph - Base class for all the event graphs which are used to allow access to a multi-level
 * hierarchy of BaseClass->SubClass dependencies. The graphs are built manually via adding dependencies.
 * Each event has one next base type (no multiple classes inheritance)
 * Any class inheriting EventTypeGraph must be a Singleton or implement static getInstance() method.
 */

#ifndef EVENTTYPEGRAPH_HPP
#define EVENTTYPEGRAPH_HPP

#include <typeindex>
#include <unordered_map>

class EventTypeGraph
{
private:
    // key - derived class, value - the next previous base class in the hierarchy
    std::unordered_map<std::type_index, std::type_index> eventPredecessorMap;
public:
    virtual ~EventTypeGraph() = default;
    bool matchesType(const std::type_index& matchID, std::type_index typeID) const;

protected:
    EventTypeGraph() = default;
    void addDependency(const std::type_index& baseTypeID, const std::type_index& derivedTypeID);
};

#endif // EVENTTYPEGRAPH_HPP
