cmake_minimum_required (VERSION 3.18) # Minimum tested version
set(CMAKE_CXX_STANDARD 17)

project(LB3)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(src)
add_subdirectory(test)
