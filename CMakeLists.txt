cmake_minimum_required(VERSION 3.5)

project(Paragon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

set(SRC_ROOT ${CMAKE_SOURCE_DIR})
include_directories(${SRC_ROOT})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(PARAGON_DEBUG)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/ParagonApp")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    cmake_path(NORMAL_PATH CMAKE_SOURCE_DIR OUTPUT_VARIABLE PROJECT_ROOT_NORMALIZED_PATH)
    add_compile_options("-ffile-prefix-map=${PROJECT_ROOT_NORMALIZED_PATH}/=")
endif()

add_subdirectory(common)
add_subdirectory(util)
add_subdirectory(core)
add_subdirectory(ParagonApp)
add_subdirectory(ParagonEditorApp)
