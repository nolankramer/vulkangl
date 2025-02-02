cmake_minimum_required(VERSION 3.19)

project(vulkangl
    VERSION 1.0.0
    DESCRIPTION "Library to help developers bridge legacy OpenGL programs to Vulkan."
    HOMEPAGE_URL "https://github.com/nolankramer/vulkangl"
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build the shared library" ON)
option(BUILD_TESTS "Build test programs" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)

# Detect if top-level
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

add_subdirectory(src)

option(vulkangl_INCLUDE_PACKAGING "Include packaging rules for vulkangl" "${is_top_level}")
if (vulkangl_INCLUDE_PACKAGING)
    add_subdirectory(packaging)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
