cmake_minimum_required(VERSION 3.0.0)
project(SamaClient VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} src/NetClient.h src/NetClient.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC SamaCommon)
target_include_directories(${PROJECT_NAME} PUBLIC src/)