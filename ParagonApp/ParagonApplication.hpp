#ifndef PARAGONAPPLICATION_HPP
#define PARAGONAPPLICATION_HPP

#include <common/Application.hpp>
#include <common/ApplicationScene.hpp>

#include <memory>
#include <typeindex>

#include "state/ParagonStateManager.hpp"
#include "system/ui/UIEntityManager.hpp"

class ParagonApplication : public Application
{
private:
    std::unique_ptr<ParagonStateManager> stateManager;
public:
    ParagonApplication();
    void init() override;
    void update() override;
    ApplicationType getApplicationType() const override;
    const ApplicationScene& getCurrentScene() const;
};

#endif // PARAGONAPPLICATION_HPP
