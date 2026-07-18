file(GLOB UTIL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(util STATIC ${UTIL_SOURCES}
    Math.cpp)

set_target_properties(util PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(util PRIVATE /usr/include/lua5.4)

target_link_libraries(util
    PRIVATE
    lua5.4
)
