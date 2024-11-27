cmake_minimum_required(VERSION 3.30)
project(ParallelizationOfBubbleSort)

set(CMAKE_CXX_STANDARD 20)

# Find OpenMP
find_package(OpenMP REQUIRED)

add_executable(ParallelizationOfBubbleSort main.cpp)

# Link OpenMP to the target
if(OpenMP_CXX_FOUND)
    target_link_libraries(ParallelizationOfBubbleSort PUBLIC OpenMP::OpenMP_CXX)
endif()
