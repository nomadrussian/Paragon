#ifndef KEYBOARDLISTENER_HPP
#define KEYBOARDLISTENER_HPP

#include <common/Event.hpp>
#include <common/EventListener.hpp>

class KeyboardListener : public EventListener
{
public:
    KeyboardListener();
    ~KeyboardListener() = default;
    void init() override;
    void onEvent(const Event& event) override;
};

#endif // KEYBOARDLISTENER_HPP
