cmake_minimum_required(VERSION 3.12)
project(OpenCL_Tutorial_in_Codes)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCL REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)
