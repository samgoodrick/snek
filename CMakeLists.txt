cmake_minimum_required(VERSION 2.8)
project(snek)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

Find_Package(SDL REQUIRED)

link_libraries( ${SDL_LIBRARY} )

add_executable(snek ../src/main.cpp ../src/collision.cpp ../src/snek.cpp ../src/wall.cpp)
