cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 11)
project(water-supply-analysis)

set(H_FILES
        src/Station.h
        #...
)

set(CPP_FILES
        #...
        src/main.cpp
        src/Reservoir.cpp
        src/City.cpp
        src/NodeInfo.cpp
        src/Edge.cpp
        src/Vertex.cpp
        src/Graph.cpp
        src/DataLoader.cpp
        src/DataHandler.cpp
)

add_executable(water-supply-analysis
        ${H_FILES} ${CPP_FILES})