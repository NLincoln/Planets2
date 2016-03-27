cmake_minimum_required(VERSION 3.3)
project(Planets)

find_package(CGAL QUIET COMPONENTS Core)

if (CGAL_FOUND)
    include( ${CGAL_USE_FILE} )
    include( CGAL_CreateSingleSourceCGALProgram)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++14")

set(SOURCE_FILES
    src/Common.h
    src/GraphManager.h
    src/Main.cpp
    src/Planet.cpp
    src/Planet.h src/Ore.cpp src/Ore.h src/Ship.cpp src/Ship.h src/GraphManager.cpp)

add_executable(Planets ${SOURCE_FILES})