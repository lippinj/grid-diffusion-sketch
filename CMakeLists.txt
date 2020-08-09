cmake_minimum_required(VERSION 3.1)

project(grid-diffusion)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

include_directories(
    include
    third_party/catch2
)

add_executable(
    grid-diffusion
    src/main.cpp
)

add_executable(
    grid-diffusion-tests
    test/testmain.cpp
    test/traversals.test.cpp
)