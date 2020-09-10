cmake_minimum_required(VERSION 3.15)
project(GaussMethod)

set(CMAKE_CXX_STANDARD 14)
set(EIGEN_DIR /home/alexis/eigen/eigen-3.3.7/)
include_directories(${EIGEN_DIR})
add_executable(GaussMethod Round.cpp Round.h Vector.h Vector.cpp Matrix.h Matrix.cpp main.cpp)
target_link_libraries(GaussMethod ${EIGEN_DIR})