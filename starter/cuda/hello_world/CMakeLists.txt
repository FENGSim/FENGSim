cmake_minimum_required(VERSION 3.15)
project(CUDA_Examples)

# Enable CUDA support
enable_language(CUDA)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify CUDA compiler (optional, CMake usually auto-detects)
set(CMAKE_CUDA_COMPILER /usr/bin/nvcc)

# Set CUDA host compiler to g++-13
set(CMAKE_CUDA_HOST_COMPILER /usr/bin/g++-13)

# Set CUDA architecture flags (adjust based on your GPU)
# Common values: 61 (Pascal), 75 (Turing), 86 (Ampere), 89 (Ada)
set(CMAKE_CUDA_ARCHITECTURES 61)

# Add executable
add_executable(test test.cu)
