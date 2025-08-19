#include "UIEntityManager.hpp"

#define entry(component_type, storage_type) \
{ \
    typeid(component_type), \
    [this](EntityID entity) \
    { \
        this->template addUIComponentFunction<storage_type<component_type>>(entity); \
    } \
}

UIEntityManager::UIEntityManager()
{
    addUIComponentFunctionMap = {
        entry(UIButtonComponent, UIComponentMap),
        entry(UISliderComponent, UIComponentMap),
        entry(UIHoverableComponent, UIComponentListWithEntityIDs),
        entry(UITextureComponent, UIComponentListWithEntityIDs),
        entry(UITransform2DComponent, UIComponentListWithEntityIDs),
        entry(UITextComponent, UIComponentListWithEntityIDs)
    };
}

#undef entry

EntityID UIEntityManager::createNewEntity()
{
    EntityID newEntity = nextEntityID;
    nextEntityID++;
    return newEntity;
}

void UIEntityManager::removeEntity(EntityID entity)
{

}

void UIEntityManager::removeAllEntities()
{

}

bool UIEntityManager::entityExists(EntityID entity)
{

}
