add_executable(ze_fh main.cpp)

add_subdirectory(core)

target_link_libraries(ze_fh PRIVATE ze_fh_core)
