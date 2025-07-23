file(GLOB COMMON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(common STATIC ${COMMON_SOURCES})

target_include_directories(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/../external/include
)

target_link_libraries(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/libmsdfgen-core.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/libmsdfgen-ext.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/libmsdf-atlas-gen.a
)
