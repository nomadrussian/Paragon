file(GLOB UTIL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.hpp"
)

add_library(util STATIC ${UTIL_SOURCES})

set_target_properties(util PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(util PUBLIC /usr/include/lua5.4)

find_package(GLEW REQUIRED)

target_link_libraries(util
    PRIVATE
    lua5.4
)
