cmake_minimum_required(VERSION 3.0.0)
project(Sama VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(Sama/Common)
add_subdirectory(Sama/Server)
add_subdirectory(Sama/Client)
add_subdirectory(Sama/Tests)

add_subdirectory(examples)
