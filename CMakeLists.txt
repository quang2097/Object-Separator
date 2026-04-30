cmake_minimum_required(VERSION 3.10)

project(ObjectSeparator CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(ObjectSeparator_program
    src/main.cpp
    src/input.cpp
    src/output.cpp
    src/processing.cpp
    src/utils/announceError.cpp
)

target_include_directories(ObjectSeparator_program PRIVATE
    include
)

find_package(OpenCV REQUIRED PATHS libs/opencv_cpp/build)

target_link_libraries(ObjectSeparator_program PRIVATE ${OpenCV_LIBS})