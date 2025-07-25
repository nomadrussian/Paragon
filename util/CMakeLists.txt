file(GLOB UTIL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(util STATIC ${UTIL_SOURCES})

set_target_properties(util PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(GLEW REQUIRED)
