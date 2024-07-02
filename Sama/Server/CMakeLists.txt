cmake_minimum_required(VERSION 3.0.0)
project(SamaServer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} src/Server.h src/Server.cpp)
