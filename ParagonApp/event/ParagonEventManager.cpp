#include "ParagonEventManager.hpp"

#include <util/Log.hpp>

#include <cassert>
#include <string>
#include <typeinfo>

template<>
ParagonEventManager* Singleton<ParagonEventManager>::instance = nullptr;
