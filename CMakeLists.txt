# Define project settings.
cmake_minimum_required (VERSION 2.6) 
project (RCRand  C) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_C_FLAGS  "-g -Wall -O2 -lpthread")


# Build executable.
file(GLOB_RECURSE src_files
  "src/*.h"
  "src/*.c"
)
add_executable(rcrand ${src_files})