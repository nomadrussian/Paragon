file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_executable(ParagonEditorApp ${EDITOR_SOURCES})

target_include_directories(ParagonEditorApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ParagonEditorApp PRIVATE
    common core util
)
