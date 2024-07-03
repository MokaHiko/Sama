cmake_minimum_required(VERSION 3.0.0)

project(SamaExamples VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} client.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SamaClient)