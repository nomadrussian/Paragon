#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <util/Log.hpp>

#include <algorithm>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "Entity.hpp"

struct Component
{
protected:
    Component() = default;
    Component& operator=(const Component&) = delete;
    Component(const Component&) = delete;
    Component(Component&&) = default;
    Component& operator=(Component&&) = default;
    virtual ~Component() = default;
};

template<typename T>
concept ComponentDerivedType = std::is_base_of_v<Component, T>;

template<EntityIDType EntityIDT>
class ComponentStorage
{
public:
    virtual void addEntity(EntityIDT entity) = 0;
    virtual void removeEntity(EntityIDT entity) = 0;
    virtual bool hasEntity(EntityIDT entity) const = 0;
    virtual void* getComponentRaw(EntityIDT entity) = 0;
    virtual size_t getNumberOfEntities() const = 0;
    virtual void removeAllEntities() = 0;
};

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
    void addEntity(EntityIDT entity) override
    {
        if (hasEntity(entity))
        {
            log_warning(
                std::string("Attempt to add entity ") + std::to_string(entity) + std::string(" to ") +
                typeid(ComponentT).name() + std::string(" map when it already has such component.")
            );
            return;
        }

        componentMap.try_emplace(entity);
    }

    void removeEntity(EntityIDT entity) override
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

    bool hasEntity(EntityIDT entity) const override
    {
        return componentMap.contains(entity);
    }

    ComponentT* getComponent(EntityIDT entity)
    {
        if (!hasEntity(entity))
        {
            log_warning(
                std::string("Attempt to get component ") + typeid(ComponentT).name() + std::string(" from entity ") +
                typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity) + std::string(" which doesn't exist.")
            );
            return nullptr;
        }

        return &componentMap.at(entity);
    }

    void* getComponentRaw(EntityIDT entity) override
    {
        return static_cast<void*>(getComponent(entity));
    }

    size_t getNumberOfEntities() const override
    {
        return componentMap.size();
    }

    void removeAllEntities() override
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
    void addEntity(EntityIDT entity) override
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
        componentList.emplace_back();
        entityToIndexMap[entity] = entityList.size() - 1;
    }

    void removeEntity(EntityIDT entity) override
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

    bool hasEntity(EntityIDT entity) const override
    {
        return entityToIndexMap.contains(entity);
    }

    ComponentT* getComponent(EntityIDT entity)
    {
        if (!hasEntity(entity))
        {
            log_warning(
                std::string("Attempt to get component ") + typeid(ComponentT).name() + std::string(" from entity ") +
                typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity) + std::string(" which doesn't exist.")
            );
            return nullptr;
        }

        return &componentList.at(getEntityIndex(entity));
    }

    void* getComponentRaw(EntityIDT entity) override
    {
        return static_cast<void*>(getComponent(entity));
    }

    size_t getEntityIndex(EntityIDT entity) const
    {
        auto iterator = entityToIndexMap.find(entity);
        return iterator != entityToIndexMap.end() ? iterator->second : static_cast<size_t>(ENTITY_NOTFOUND<EntityIDT>);
    }

    size_t getNumberOfEntities() const override
    {
        return componentList.size();
    }

    void removeAllEntities() override
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
