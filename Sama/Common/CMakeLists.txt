cmake_minimum_required(VERSION 3.0.0)
project(SamaCommon VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} src/NetCommon.h src/NetCommon.cpp src/NetMessage.h src/TSQueue.h src/TSQueue.cpp src/NetClient.h)

set(ASIO_INCLUDE_DIR "/Users/caltax/dev/Libraries/asio-1.26.0/include")
target_include_directories(${PROJECT_NAME} PUBLIC ${ASIO_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC src/)