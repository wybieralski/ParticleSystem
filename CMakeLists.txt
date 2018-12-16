cmake_minimum_required(VERSION 3.12)
project(Particles)

set(CMAKE_CXX_STANDARD 17)

add_executable(Particles main.cpp Screen.cpp Swarm.cpp Particle.cpp)
#include_directories("/usr/include/SDL")
#target_link_libraries(Particles "/usr/lib/x86_64-linux-gnu/libSDL.so")
include_directories("/usr/include/SDL2")
target_link_libraries(Particles "/usr/lib/x86_64-linux-gnu/libSDL2.so")
