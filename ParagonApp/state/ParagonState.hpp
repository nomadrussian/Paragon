#ifndef PARAGONSTATE_HPP
#define PARAGONSTATE_HPP

#include <common/EventListener.hpp>

class ParagonState : public EventListener
{
public:
    ParagonState();
    virtual ~ParagonState();
    virtual void onEntry() = 0;
    virtual void onLeave() = 0;
    void init() override;
    void onEvent(const Event& event) override;
};

#endif // PARAGONSTATE_HPP
