#ifndef PARAGONSTATEMANAGER_HPP
#define PARAGONSTATEMANAGER_HPP

#include <memory>
#include <ParagonApp/scene/ParagonScene.hpp>

#include "ParagonState.hpp"

class ParagonStateManager
{
private:
    std::unique_ptr<ParagonState> currentState;
public:
    ParagonStateManager();
    ~ParagonStateManager() = default;
    const std::type_info& getCurrentStateTypeID() const;
    const ParagonScene& getCurrentScene() const;
};

#endif // PARAGONSTATEMANAGER_HPP
