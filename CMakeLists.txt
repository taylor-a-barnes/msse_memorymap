cmake_minimum_required(VERSION 3.14)

# Project name and version
project(MemoryMap VERSION 1.0
              DESCRIPTION "Map out the virtual memory of a small code"
              LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add the executable
add_executable(memorymap src/main.cpp)
