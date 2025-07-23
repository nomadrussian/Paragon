#include "KeyboardListener.hpp"

#include <core/event/CoreEventManager.hpp>
#include <core/event/CoreEventTypeGraph.hpp>
#include <core/event/InputEvent.hpp>
#include <core/render/RenderHandler.hpp>
#include <util/Log.hpp>

#include <cmath>
#include <typeindex>

#include <glm/glm.hpp>

KeyboardListener::KeyboardListener()
{
}

void KeyboardListener::init()
{
    CoreEventManager::getInstance().subscribe<KeyboardKeyIsHeldEvent>(shared_from_this());
}

void KeyboardListener::onEvent(const Event& event)
{
    if(!CoreEventTypeGraph::getInstance().matchesType(typeid(KeyboardEvent), typeid(event)))
    {
        log_warning("KeyListener got a non-KeyboardEvent event");
        return;
    }

    int id;
    try {
        const KeyboardKeyIsHeldEvent& k_event = dynamic_cast<const KeyboardKeyIsHeldEvent&>(event);
        id = k_event.getKeyID();

        // Plug, will be replaced
        Camera& camera = RenderHandler::getInstance().getCamera();
        float c_sin = std::sin(glm::radians(camera.getOrientation().y));
        float c_cos = std::cos(glm::radians(camera.getOrientation().y));
        switch(id)
        {
            case 'W':
                camera.move(glm::vec3(0.05f * c_cos, 0.0f, 0.05f * c_sin));
                break;
            case 'S':
                camera.move(glm::vec3(-0.05f * c_cos, 0.0f, -0.05f * c_sin));
                break;
            case 'A':
                camera.move(glm::vec3(0.05f * c_sin, 0.0f, -0.05f * c_cos));
                break;
            case 'D':
                camera.move(glm::vec3(-0.05f * c_sin, 0.0f, 0.05f * c_cos));
                break;
            case ' ':
                camera.move(glm::vec3(0.0f, 0.05f, 0.0f));
                break;
            case 341:
                camera.move(glm::vec3(0.0f, -0.05f, 0.0f));
                break;
            case 265:
                camera.rotate(glm::vec3(0.8f, 0.0f, 0.0f));
                break;
            case 264:
                camera.rotate(glm::vec3(-0.8f, 0.0f, 0.0f));
                break;
            case 263:
                camera.rotate(glm::vec3(0.0f, -0.8f, 0.0f));
                break;
            case 262:
                camera.rotate(glm::vec3(0.0f, 0.8f, 0.0f));
                break;
        }
    }  catch (const std::bad_cast& e) {
        log_warning("Bad cast while processing dynamic_cast<const KeyboardKeyIsHeldEvent&>(event)");
        return;
    }
}

