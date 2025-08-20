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

#include "UIComponent.hpp"
#include "UIEntity.hpp"

class UIEntityManager : public EntityManager<UIEntityID>, public Singleton<UIEntityManager>
{
    friend class Singleton<UIEntityManager>;
private:
    ComponentStorageMap<UIClickComponent, UIEntityID> UIClickButtonComponentMap;
    ComponentStorageMap<UIPushComponent, UIEntityID> UIPushButtonComponentMap;
    ComponentStorageMap<UISliderComponent, UIEntityID> UISliderComponentMap;

    ComponentStorageList<UIHoverableComponent, UIEntityID> UIHoverableComponentList;
    ComponentStorageList<UITextureComponent, UIEntityID> UITextureComponentList;
    ComponentStorageList<UITransform2DComponent, UIEntityID> UITransform2DComponentList;
    ComponentStorageList<UITextComponent, UIEntityID> UITextComponentList;

    std::unordered_map<std::type_index, ComponentStorage<UIEntityID>*> UIComponentStorageCorrespondenceMap;

public:
    using EntityManager<UIEntityID>::addComponent;
    using EntityManager<UIEntityID>::removeComponent;

    void updateSystems();

protected:
    UIEntityManager() = default;
    ~UIEntityManager() = default;
};

#endif // UIENTITYMANAGER_HPP
