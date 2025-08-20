#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <util/Log.hpp>

#include <typeindex>
#include <unordered_map>
#include <unordered_set>

#include "Component.hpp"
#include "Entity.hpp"
#include "Singleton.hpp"

template<EntityIDType EntityIDT>
class EntityManager
{
protected:
    EntityIDT nextEntityID = 0;
    std::unordered_map<std::type_index, ComponentStorage<EntityIDT>*> componentStorageCorrespondenceMap;
    std::unordered_set<EntityIDT> existingEntities;

public:
    EntityManager() = default;
    virtual ~EntityManager() = default;

    /*
     * Use the returned pointer only for the component setup, otherwise it might become invalid
     * if a storage shuffles data internally - it might be pointing to another component or to nothing.
     * TLDR: Storing the pointer for postponed use is undefined behaviour.
     */
    template<ComponentDerivedType ComponentT>
    ComponentT* addComponent(EntityIDT entity)
    {
        std::type_index componentTypeIndex = typeid(ComponentT);

        if (!entityExists(entity))
        {
            log_warning(
                std::string("Failed attempt to add component ") + componentTypeIndex.name() + std::string(": Entity ") +
                typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity) + std::string(" doesn't exist.")
            );
            return nullptr;
        }

        auto pStorage = componentStorageCorrespondenceMap.find(componentTypeIndex);

        if (pStorage != componentStorageCorrespondenceMap.end())
        {
            pStorage->second->addEntity(entity);
        }
        else
        {
            log_error(
                std::string("Unable to find corresponding ComponentStorage for ") + componentTypeIndex.name() +
                std::string(" when attempting to add it to entity ") + typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity)
            );
            return nullptr;
        }
    }

    /*
     * The same caution - returned pointer is valid only right after the function is called.
     * Storing the pointer for postponed use is undefined behaviour.
     */
    template<ComponentDerivedType ComponentT>
    ComponentT* getComponent(EntityIDT entity) const
    {
        std::type_index componentTypeIndex = typeid(ComponentT);

        if (!entityExists(entity))
        {
            log_warning(
                std::string("Failed attempt to get component ") + componentTypeIndex.name() + std::string(": Entity ") +
                typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity) + std::string(" doesn't exist.")
            );
            return nullptr;
        }

        auto pStorage = componentStorageCorrespondenceMap.find(componentTypeIndex);

        if (pStorage != componentStorageCorrespondenceMap.end())
        {
            return pStorage->second.getComponent(entity);
        }
        else
        {
            log_error(
                std::string("Unable to find corresponding ComponentStorage for ") + componentTypeIndex.name() +
                std::string(" when attempting to get it from entity ") + typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity)
            );

            return nullptr;
        }
    }

    template<ComponentDerivedType ComponentT>
    void removeComponent(EntityIDT entity)
    {
        std::type_index componentTypeIndex = typeid(ComponentT);

        if (!entityExists(entity))
        {
            log_warning(
                std::string("Failed attempt to remove component ") + componentTypeIndex.name() + std::string(": Entity ") +
                typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity) + std::string(" doesn't exist.")
            );
            return;
        }

        auto pStorage = componentStorageCorrespondenceMap.find(componentTypeIndex);

        if (pStorage != componentStorageCorrespondenceMap.end())
        {
            pStorage->second->removeEntity(entity);
        }
        else
        {
            log_error(
                std::string("Unable to find corresponding ComponentStorage for ") + componentTypeIndex.name() +
                std::string(" when attempting to remove it from entity ") + typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity)
            );
        }
    }

    virtual EntityIDT createNewEntity()
    {
        EntityIDT newEntity = nextEntityID;
        nextEntityID++;

        existingEntities.insert(newEntity);

        return newEntity;
    }

    virtual bool entityExists(EntityIDT entity) const
    {
        if (entity >= nextEntityID)
        {
            return false;
        }

        return existingEntities.contains(entity);
    }

    virtual void removeAllEntities()
    {
        existingEntities.clear();

        for (auto& [type, pStorage] : componentStorageCorrespondenceMap)
        {
            log_debug(std::string("Clearing storage of ") + type.name() + std::string(" for ") + typeid(EntityIDT).name());
            pStorage->removeAllEntities();
        }
    }

    virtual void removeEntity(EntityIDT entity)
    {
        if (!entityExists(entity))
        {
            log_warning(std::string("Bad attempt to remove non-existent entity ") + typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity));
            return;
        }

        for (auto& [type, pStorage] : componentStorageCorrespondenceMap)
        {
            log_debug(std::string("Removing component ") + type.name() + std::string("from entity ") + typeid(EntityIDT).name() + std::string(" #") + std::to_string(entity));
            pStorage->removeEntity(entity);
        }
    }
};

#endif // ENTITYMANAGER_HPP
