cmake_minimum_required(VERSION 3.14)

project(RM_RayTracer)

option(
    BUILD_SANDBOX
    "Build The Sandbox Project Alongside The Library"
    OFF
)

option(
    BUILD_TESTS
    "Build Test Suite Alongside The Library"
    OFF
)

option(
    BUILD_ALL
    "Build Tests and Sandbox Projects Alongside The Library"
    OFF
)

set(VENDOR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/include")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (BUILD_SANDBOX)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Raytracer_Sandbox ${CMAKE_CURRENT_BINARY_DIR}/Raytracer_Sandbox)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Raytracer_Sandbox)
endif ()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tests ${CMAKE_CURRENT_BINARY_DIR}/Tests)
endif ()

if (BUILD_ALL)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tests ${CMAKE_CURRENT_BINARY_DIR}/Tests)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Raytracer_Sandbox ${CMAKE_CURRENT_BINARY_DIR}/Raytracer_Sandbox)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Raytracer_Sandbox)
endif ()
