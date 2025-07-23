#ifndef INPUTEVENT_HPP
#define INPUTEVENT_HPP

#include "CoreEvent.hpp"

class InputEvent : public CoreEvent
{
};

class KeyboardEvent : public InputEvent
{
protected:
    int keyID;
public:
    KeyboardEvent(const int& key) : keyID(key) {}
    const int& getKeyID() const { return keyID; }
};

class KeyboardKeyPressedEvent : public KeyboardEvent
{
public:
    KeyboardKeyPressedEvent(const int& key) : KeyboardEvent(key) {}
};

class KeyboardKeyReleasedEvent : public KeyboardEvent
{
public:
    KeyboardKeyReleasedEvent(const int& key) : KeyboardEvent(key) {}
};

class KeyboardKeyIsHeldEvent : public KeyboardEvent
{
public:
    KeyboardKeyIsHeldEvent(const int& key) : KeyboardEvent(key) {}
};

class MouseEvent : public InputEvent
{
};

class MouseMovedEvent : public MouseEvent
{
private:
    float delta_x, delta_y;
public:
    MouseMovedEvent(double dx, double dy) : delta_x(dx), delta_y(dy) {};
    float getDX() const { return delta_x; }
    float getDY() const { return delta_y; }
};

class MouseButtonPressedEvent : public MouseEvent
{
};

class MouseButtonReleasedEvent : public MouseEvent
{
};

class MouseButtonIsHeldEvent : public MouseEvent
{
};

#endif // INPUTEVENT_HPP
