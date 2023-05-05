cmake_minimum_required(VERSION 3.12)

project(TinyNeural, CXX)

add_executable(TinyNeural main.cpp neuralnetwork.cpp layer.cpp math_funcs.cpp)

set(CMAKE_CXX_STANDARD 14)