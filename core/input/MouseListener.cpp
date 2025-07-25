#include "MouseListener.hpp"

#include <core/Core.hpp>
#include <core/event/CoreEventManager.hpp>
#include <core/event/InputEvent.hpp>
#include <core/render/Camera.hpp>
#include <core/render/RenderHandler.hpp>

MouseListener::MouseListener()
{
}

void MouseListener::init()
{
    CoreEventManager::getInstance().subscribe<MouseMovedEvent>(shared_from_this());
}

void MouseListener::onEvent(const Event& event)
{
    if(!CoreEventTypeGraph::getInstance().matchesType(typeid(MouseEvent), typeid(event)))
    {
        log_warning("MouseListener got a non-MouseEvent event");
        return;
    }

    float dx, dy;
    try {
        const MouseMovedEvent& r_event = dynamic_cast<const MouseMovedEvent&>(event);

        float delta_time = Core::getInstance().getDeltaTime();
        dx = r_event.getDX() * delta_time * 5.0f;
        dy = r_event.getDY() * delta_time * 5.0f;

        // Plug, will be replaced
        Camera& camera = RenderHandler::getInstance().getCamera();
        camera.rotate(glm::vec3(dy, dx, 0.0f));
    }  catch (const std::bad_cast& e) {
        log_warning("Bad cast while processing dynamic_cast<const MouseMovedEvent&>(event)");
        return;
    }
}
