cmake_minimum_required(VERSION 3.0.0)

project(SamaExamples VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} example_server/server.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SamaServer)
