cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(gdt_api)

file(COPY "conf" DESTINATION ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data/meas)

add_subdirectory(src)

set_target_properties(fengsim_meas PROPERTIES RUNTIME_OUTPUT_DIRECTORY "./../")
