#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <util/Log.hpp>

#include <typeindex>
#include <unordered_map>

#include "Component.hpp"
#include "Entity.hpp"

template<EntityIDType EntityIDT>
class EntityManager
{
protected:
    EntityIDT nextEntityID = 0;
    std::unordered_map<std::type_index, ComponentStorage<EntityIDT>*> UIComponentStorageCorrespondenceMap;

public:
    template<ComponentDerivedType ComponentT>
    void addUIComponent(EntityIDT entity)
    {
        std::type_index componentTypeIndex = typeid(ComponentT);
        auto pStorage = UIComponentStorageCorrespondenceMap.find(componentTypeIndex);
        if (pStorage != UIComponentStorageCorrespondenceMap.end())
        {
            pStorage->second->addEntity(entity);
        }
        else
        {
            log_error(std::string("Unable to find corresponding addUIComponentFunction for ") + componentTypeIndex.name());
        }
    }

    virtual ~EntityManager() = default;
    virtual EntityIDT createNewEntity() = 0;
    virtual void removeEntity(EntityIDT entity) = 0;
    virtual void removeAllEntities() = 0;
    virtual bool entityExists(EntityIDT entity) = 0;
};

#endif // ENTITYMANAGER_HPP
