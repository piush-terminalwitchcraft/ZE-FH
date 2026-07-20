cmake_minimum_required(VERSION 3.16)
project(ze_fh)

if(NOT CMAKE_BUILD_TYPE)
  set(default_build_type "Debug")
  message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Choose the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "ze_fh Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for ze_fh
set(ze_fh_Version_Major 0)
set(ze_fh_Version_Minor 1)
set(ze_fh_Version_Patch 0)
set(ze_fh_Version_Status "-dev")
set(PROJECT_VERSION
  "${ze_fh_Version_Major}.${ze_fh_Version_Minor}.${ze_fh_Version_Patch}${ze_fh_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

file(GLOB FH_SOURCES "*.cpp")
file(GLOB FH_HEADERS "include/*.h")

# Create library for fh (configuration / helper code)
add_library(ze_fh ${FH_SOURCES} ${FH_HEADERS}
        include/ZE/FH/MarketDataFeedHandler.h
        include/ZE/FH/MarketDataDispatcher.h)
target_include_directories(ze_fh PUBLIC include ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(ze_fh PUBLIC ze_core)

configure_file(app.conf ${CMAKE_BINARY_DIR}/app.conf)
