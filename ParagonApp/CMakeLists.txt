file(GLOB PARAGON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/config/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/config/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/actor/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/actor/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/character/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/character/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/light/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/light/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/static/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/static/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/ui/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ecs/ui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/scene/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/scene/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/state/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/state/*.cpp"
)

add_executable(ParagonApp ${PARAGON_SOURCES})

set_target_properties(ParagonApp
    PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN"
    RPATH "$ORIGIN"
)

target_include_directories(ParagonApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(util PUBLIC /usr/include/lua5.4)

find_package(GLEW REQUIRED)
target_link_libraries(ParagonApp PRIVATE
    common core util
)

target_link_libraries(ParagonApp
    PRIVATE
    lua5.4
)

add_custom_command(
    TARGET ParagonApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/scripts
            ${CMAKE_CURRENT_BINARY_DIR}/../scripts
)

