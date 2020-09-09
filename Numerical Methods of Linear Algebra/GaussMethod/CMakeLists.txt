cmake_minimum_required(VERSION 3.15)
project(GaussMethod)

set(CMAKE_CXX_STANDARD 14)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(GaussMethod Round.cpp Round.h Vector.h Vector.cpp Matrix.h Matrix.cpp main.cpp)
target_link_libraries (Eigen3::Eigen)
