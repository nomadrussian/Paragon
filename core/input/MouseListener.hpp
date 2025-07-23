#ifndef MOUSELISTENER_HPP
#define MOUSELISTENER_HPP

#include <common/Event.hpp>
#include <common/EventListener.hpp>

class MouseListener : public EventListener
{
public:
    MouseListener();
    ~MouseListener() = default;
    void init() override;
    void onEvent(const Event& event) override;
};

#endif // MOUSELISTENER_HPP
