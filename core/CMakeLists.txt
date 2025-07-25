file(GLOB CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/asset/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/asset/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/input/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/input/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/render/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/render/*.cpp"
)

add_library(core SHARED ${CORE_SOURCES})

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SRC_ROOT}/external/include
)

find_package(GLEW REQUIRED)
target_link_libraries(core
    PRIVATE
        common util
        glfw GLEW::GLEW GL X11 pthread Xrandr Xi dl
)

set_target_properties(core
    PROPERTIES
        INSTALL_RPATH "$ORIGIN/../external"
        BUILD_RPATH "$ORIGIN/../external"
)
