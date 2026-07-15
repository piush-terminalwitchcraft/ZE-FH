cmake_minimum_required(VERSION 3.16)
project(ze_fh_core)

if(NOT CMAKE_BUILD_TYPE)
  set(default_build_type "Debug")
  message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Chooce the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "ze_fh_core Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for ze_fh_core
set(ze_fh_core_Version_Major 0)
set(ze_fh_core_Version_Minor 1)
set(ze_fh_core_Version_Patch 0)
set(ze_fh_core_Version_Status "-dev")
set(PROJECT_VERSION
  "${ze_fh_core_Version_Major}.${ze_fh_core_Version_Minor}.${ze_fh_core_Version_Patch}${ze_fh_core_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

file(GLOB CORE_SOURCES "*.cpp")
file(GLOB CORE_HEADERS "include/*.h")

add_library(ze_fh_core ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(ze_fh_core PUBLIC include)
