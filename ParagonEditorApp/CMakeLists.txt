file(GLOB EDITOR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_executable(ParagonEditorApp ${EDITOR_SOURCES})

target_include_directories(ParagonEditorApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(GLEW REQUIRED)
target_link_libraries(ParagonEditorApp PRIVATE
    common core util
)
