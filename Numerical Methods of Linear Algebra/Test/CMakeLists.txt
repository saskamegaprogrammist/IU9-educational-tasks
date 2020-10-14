
cmake_minimum_required(VERSION 3.15)
project(Test)

set(CMAKE_CXX_STANDARD 14)
set(EIGEN_DIR /home/alexis/eigen/eigen-3.3.7/)
include_directories(${EIGEN_DIR})
add_executable(Test ../Primitives/Vector.h ../Primitives/Vector.cpp
        ../Primitives/Matrix.h ../Primitives/Matrix.cpp ../GaussMethod/LASolver.cpp ../GaussMethod/LASolver.h
        ../IterationMethods/JakobiMethod.cpp ../IterationMethods/JakobiMethod.h main.cpp)
target_link_libraries(Test ${EIGEN_DIR})