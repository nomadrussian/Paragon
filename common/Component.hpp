#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <util/Log.hpp>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "Entity.hpp"

struct Component
{
protected:
    Component() = default;
    Component& operator=(const Component&) = delete;
    Component(const Component&) = delete;
    Component(Component&&) = delete;
    virtual ~Component() = default;
};

template<EntityIDType EntityIDT>
class ComponentStorage
{
public:
    virtual void addEntity(EntityIDT entity) = 0;
    virtual void removeEntity(EntityIDT entity) = 0;
    virtual bool hasEntity(EntityIDT entity) const = 0;
    virtual size_t getNumberOfEntities() const = 0;
    virtual void removeAllEntities() = 0;
};

template<typename T>
concept ComponentDerivedType = std::is_base_of_v<Component, T>;

/*
 * We use std::unordered_map for components that are not processed frequently,
 * and we use two "std::vector"s e.g. with components that are accessed constantly like
 * every frame: in that case we need to process all the entities going through them by for loop.
 * In the first case we aim for quick O(1) lookup time;
 * In the second case we rely on the cache-friendly layout so our CPU doesn't cry.
 */

template<ComponentDerivedType ComponentT, EntityIDType EntityIDT>
class ComponentStorageMap : public ComponentStorage<EntityIDT>
{
private:
    std::unordered_map<EntityIDT, ComponentT> componentMap;

public:
    void addEntity(EntityIDT entity)
    {
        if (hasEntity(entity))
        {
            log_warning(
                std::string("Attempt to add entity ") + std::to_string(entity) + std::string(" to ") +
                typeid(ComponentT).name() + std::string(" map when it already has such component.")
            );
            return;
        }

        componentMap[entity] = ComponentT();
    }

    void removeEntity(EntityIDT entity)
    {
        if (!hasEntity(entity))
        {
            log_warning(
                std::string("Attempt to remove entity ") + std::to_string(entity) + std::string(" from ") +
                typeid(ComponentT).name() + std::string(" map when it doesn't have such component.")
            );
            return;
        }

        componentMap.erase(entity);
    }

    bool hasEntity(EntityIDT entity) const
    {
        return componentMap.find(entity) != componentMap.end();
    }

    size_t getNumberOfEntities() const
    {
        return componentMap.size();
    }

    void removeAllEntities()
    {
        componentMap.clear();
    }

    const std::unordered_map<EntityIDT, ComponentT>& getComponentMap() const
    {
        return componentMap;
    }
};

template<ComponentDerivedType ComponentT, EntityIDType EntityIDT>
class ComponentStorageList : public ComponentStorage<EntityIDT>
{
private:
    std::vector<ComponentT> componentList;
    std::vector<EntityIDT> entityList;
    std::unordered_map<EntityIDT, size_t> entityToIndexMap;

public:
    void addEntity(EntityIDT entity)
    {
        if (hasEntity(entity))
        {
            log_warning(
                std::string("Attempt to add entity ") + std::to_string(entity) + std::string(" to ") +
                typeid(ComponentT).name() + std::string(" list when it already has such component.")
            );
            return;
        }

        entityList.push_back(entity);
        componentList.push_back(ComponentT());
        entityToIndexMap[entity] = entityList.size() - 1;
    }

    void removeEntity(EntityIDT entity)
    {
        size_t index = getEntityIndex(entity);

        if (index == ENTITY_NOTFOUND<EntityIDT>)
        {
            log_warning(
                std::string("Attempt to remove entity ") + std::to_string(entity) + std::string(" from ") +
                typeid(ComponentT).name() + std::string(" list when it doesn't have such component.")
            );
            return;
        }

        size_t lastIndex = entityList.size() - 1;
        if (index != lastIndex)
        {
            EntityIDT lastEntity = entityList.back();
            entityToIndexMap[lastEntity] = index;
            std::swap(entityList[index], entityList.back());
            std::swap(componentList[index], componentList.back());
        }

        entityList.pop_back();
        componentList.pop_back();
        entityToIndexMap.erase(entity);
    }

    bool hasEntity(EntityIDT entity) const
    {
        return entityToIndexMap.find(entity) != entityToIndexMap.end();
    }

    size_t getEntityIndex(EntityIDT entity) const
    {
        auto iterator = entityToIndexMap.find(entity);
        return iterator != entityToIndexMap.end() ? iterator->second : static_cast<size_t>(ENTITY_NOTFOUND<EntityIDT>);
    }

    size_t getNumberOfEntities() const
    {
        return componentList.size();
    }

    void removeAllEntities()
    {
        componentList.clear();
        entityList.clear();
        entityToIndexMap.clear();
    }

    const std::vector<EntityIDT>& getEntityList() const
    {
        return entityList;
    }

    const std::vector<ComponentT>& getComponentList() const
    {
        return componentList;
    }
};

#endif // COMPONENT_HPP
