cmake_minimum_required(VERSION 3.28)
project(mag2csv)

set(CMAKE_CXX_STANDARD 17)

add_executable(mag2csv main.cpp Date.cpp Magnetometer.cpp GEM.cpp Utils.cpp
        GEM.cpp
        Magnetometer.cpp)
