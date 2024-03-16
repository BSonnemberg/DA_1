cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 11)
project(water-supply-analysis)

set(H_FILES
        src/Station.h
        src/Reservoir.h
        src/City.h
        #...
)

set(CPP_FILES
        #...
        src/main.cpp
        src/Station.cpp
        src/Reservoir.cpp
        src/City.cpp
)

add_executable(water-supply-analysis
        ${H_FILES} ${CPP_FILES})