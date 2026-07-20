cmake_minimum_required(VERSION 3.16)
project(ze_core)

if(NOT CMAKE_BUILD_TYPE)
  set(default_build_type "Debug")
  message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Choose the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "ze_core Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for ze_core
set(ze_core_Version_Major 0)
set(ze_core_Version_Minor 1)
set(ze_core_Version_Patch 0)
set(ze_core_Version_Status "-dev")
set(PROJECT_VERSION
  "${ze_core_Version_Major}.${ze_core_Version_Minor}.${ze_core_Version_Patch}${ze_core_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

file(GLOB CORE_SOURCES "*.cpp")
file(GLOB CORE_HEADERS "include/*.h")

# Create library for core. Keep name independent and correct (ze_core).
add_library(ze_core ${CORE_SOURCES} ${CORE_HEADERS}
        include/ZE/Core/task.h)
target_include_directories(ze_core PUBLIC include)
