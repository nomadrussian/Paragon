#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <limits>
#include <stdlib.h>
#include <type_traits>

template<typename T>
concept EntityIDType = std::is_same_v<T, size_t>;

template<EntityIDType T>
constexpr T ENTITY_NOTFOUND = std::numeric_limits<T>::max();

#endif // ENTITY_HPP
