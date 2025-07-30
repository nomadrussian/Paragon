#ifndef PARAGONSTATEMANAGER_HPP
#define PARAGONSTATEMANAGER_HPP

#include <memory>

#include "ParagonState.hpp"

class ParagonStateManager
{
private:
    std::shared_ptr<ParagonState> currentState;
public:
    ParagonStateManager();
    ~ParagonStateManager() = default;
    const std::type_info& getCurrentStateTypeID() const;
};

#endif // PARAGONSTATEMANAGER_HPP
