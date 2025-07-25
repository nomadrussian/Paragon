file(GLOB COMMON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(common STATIC ${COMMON_SOURCES})

set_target_properties(common PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/../external/include
)
