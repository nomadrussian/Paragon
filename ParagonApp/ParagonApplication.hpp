#ifndef PARAGONAPPLICATION_HPP
#define PARAGONAPPLICATION_HPP

#include <common/Application.hpp>
#include <common/ApplicationScene.hpp>

#include <memory>

class ParagonApplication : public Application
{
private:

public:
    ParagonApplication();
    void init() override;
    ApplicationType getApplicationType() const override;
    void update() override;
};

#endif // PARAGONAPPLICATION_HPP
