file(GLOB PARAGON_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/config/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/config/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/actor/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/actor/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/character/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/character/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/light/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/light/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/static/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/static/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/ui/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/ui/*.cpp"
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

target_include_directories(ParagonApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    /usr/include/lua5.4
)

target_link_libraries(ParagonApp PRIVATE
    common core util lua5.4
)

target_link_libraries(ParagonApp
    PRIVATE
    lua5.4
)

add_custom_command(
    TARGET ParagonApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data
            ${CMAKE_CURRENT_BINARY_DIR}/../data
)

