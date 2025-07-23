#include "CoreEventTypeGraph.hpp"

#include <util/Log.hpp>

#include "InputEvent.hpp"

template<>
CoreEventTypeGraph* Singleton<CoreEventTypeGraph>::instance = nullptr;

CoreEventTypeGraph::CoreEventTypeGraph()
{
    log_debug("Adding CoreEventTypeGraph dependencies...");
    std::type_index IDInputEvent = typeid(InputEvent);
    std::type_index IDKeyboardEvent = typeid(KeyboardEvent);
    std::type_index IDMouseEvent = typeid(MouseEvent);
    addDependency(IDInputEvent, IDKeyboardEvent);
    addDependency(IDInputEvent, IDMouseEvent);
    addDependency(IDKeyboardEvent, typeid(KeyboardKeyPressedEvent));
    addDependency(IDKeyboardEvent, typeid(KeyboardKeyReleasedEvent));
    addDependency(IDKeyboardEvent, typeid(KeyboardKeyIsHeldEvent));
    addDependency(IDMouseEvent, typeid(MouseMovedEvent));
    addDependency(IDMouseEvent, typeid(MouseButtonPressedEvent));
    addDependency(IDMouseEvent, typeid(MouseButtonReleasedEvent));
    addDependency(IDMouseEvent, typeid(MouseButtonIsHeldEvent));
}
