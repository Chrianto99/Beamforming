cmake_minimum_required(VERSION 3.10)
project(BeamForming)

set(CMAKE_CXX_STANDARD 17)

add_executable(BeamForming main.cpp
        NSB.cpp
        NSB.h
        InputManager.cpp
        InputManager.h
        DataManager.cpp
        DataManager.h

)

include_directories("Eigen")

target_link_directories(BeamForming PRIVATE Koolplot)
target_link_directories(BeamForming PRIVATE Graphics)
# Include vcpkg toolchain file

# Find and link Matplotlib library


