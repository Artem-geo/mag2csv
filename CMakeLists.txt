cmake_minimum_required(VERSION 3.28)
project(mag2csv)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(mag2csv src/main.cpp src/Date.cpp src/Magnetometer.cpp src/GEM.cpp src/Utils.cpp
        src/GEM.cpp
        src/Magnetometer.cpp)
