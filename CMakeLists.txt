cmake_minimum_required (VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)

project(LightPuzzle)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_subdirectory(src)
enable_testing()
add_subdirectory(test)

