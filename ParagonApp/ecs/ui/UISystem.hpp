#ifndef INTERFACESYSTEMS_HPP
#define INTERFACESYSTEMS_HPP

class UISystem
{
public:
    virtual ~UISystem() = default;
    virtual void update(float deltaTime) = 0;
};

#endif // INTERFACESYSTEMS_HPP
