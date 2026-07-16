cmake_minimum_required(VERSION 3.16)
project(ze)

if(NOT CMAKE_BUILD_TYPE)
  set(default_build_type "Debug")
  message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Chooce the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "ze Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for ze
set(ze_Version_Major 0)
set(ze_Version_Minor 1)
set(ze_Version_Patch 0)
set(ze_Version_Status "-dev")
set(PROJECT_VERSION
  "${ze_Version_Major}.${ze_Version_Minor}.${ze_Version_Patch}${ze_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

add_subdirectory(dependencies)
add_subdirectory(src)

# Top-level executable (sources under src/)
add_executable(ze src/main.cpp)

# Link with libraries built in src/
target_link_libraries(ze PRIVATE ze_core ze_fh)
target_include_directories(ze PRIVATE ${CMAKE_SOURCE_DIR}/include)
