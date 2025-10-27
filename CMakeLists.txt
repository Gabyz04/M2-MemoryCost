cmake_minimum_required(VERSION 3.10)
project(M2-MemoryCost)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(MemoryCost)
add_subdirectory(SortingStress)
add_subdirectory(ThreadsStress)
