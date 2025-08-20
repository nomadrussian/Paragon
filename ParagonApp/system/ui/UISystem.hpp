#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

class UISystem
{
public:
    virtual ~UISystem() = default;
    virtual void update(float deltaTime) = 0;
};

#endif // UISYSTEM_HPP
