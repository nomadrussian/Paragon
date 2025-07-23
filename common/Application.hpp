/* Application - base class for executables Paragon and Editor */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>

#include "ApplicationScene.hpp"

enum ApplicationType {
    PARAGON,
    EDITOR
};

class Application
{
public:
    virtual void init() = 0;
    virtual ApplicationType getApplicationType() const = 0;
    virtual void update() = 0;
    virtual ~Application() = default;
};

#endif // APPLICATION_HPP
