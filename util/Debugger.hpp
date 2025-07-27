#ifdef PARAGON_DEBUG

#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include <common/Application.hpp>
#include <common/Singleton.hpp>
#include <core/render/RenderHandler.hpp>

class Debugger: public Singleton<Debugger>
{
    friend class Singleton<Debugger>;
private:
    ApplicationType applicationType;
public:
    void renderDebugScreen();
    void setApplicationType(ApplicationType applicationType);

protected:
    Debugger() = default;
    ~Debugger() = default;
};

#endif // DEBUGGER_HPP

#endif
