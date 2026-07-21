file(GLOB COMMON_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/asset/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/asset/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.cpp"
)

add_library(common STATIC ${COMMON_SOURCES})

set_target_properties(common PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/../external/include
)
