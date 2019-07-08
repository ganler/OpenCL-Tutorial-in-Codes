cmake_minimum_required(VERSION 3.7)

project(LearnOpenCL)
set(CMAKE_BULIE_TYPE RELEASE)
SET(CMAKE_CXX_FLAGS "-march=native -pthread -O3 -std=c++17")

set(SOURCE_FILE main.cpp)

find_package(OpenCL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILE})
target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)
