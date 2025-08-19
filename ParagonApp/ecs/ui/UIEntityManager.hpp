#ifndef UIENTITYMANAGER_HPP
#define UIENTITYMANAGER_HPP

#include <common/EntityManager.hpp>

#include <cassert>
#include <concepts>
#include <functional>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

#include "UIComponents.hpp"
#include "UIEntity.hpp"

class UIEntityManager : public EntityManager<>
{
private:
    ComponentStorageMap<UIButtonComponent> UIButtonComponentMap;
    ComponentStorageMap<UISliderComponent> UISliderComponentMap;

    ComponentStorageList<UIHoverableComponent> UIHoverableComponentList;
    ComponentStorageList<UITextureComponent> UITextureComponentList;
    ComponentStorageList<UITransform2DComponent> UITransform2DComponentList;
    ComponentStorageList<UITextComponent> UITextComponentList;

    std::unordered_map<std::type_index, ComponentStorage<UIEntityID>*> UIComponentStorageCorrespondenceMap;

public:
    UIEntityManager();
    EntityID createNewEntity() override;
    void removeEntity(EntityID entity) override;
    void removeAllEntities() override;
    bool entityExists(EntityID entity) override;

private:

};

#endif // UIENTITYMANAGER_HPP
