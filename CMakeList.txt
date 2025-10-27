cmake_minimum_required(VERSION 3.10)
project(M2_MemoryCost_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

add_subdirectory(MemoryCost)
add_subdirectory(ThreadsStress)
add_subdirectory(SortingStress)
