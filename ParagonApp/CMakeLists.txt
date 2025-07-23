file(GLOB PARAGON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event/*.cpp"
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

find_package(GLEW REQUIRED)
target_link_libraries(ParagonApp PRIVATE
    common core util
)
