cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 11)
project(water-supply-analysis)

set(H_FILES
        src/Reservoir.h
        src/Station.h
        src/City.h
        src/NodeInfo.h
        src/Vertex.h
        src/Edge.h
        src/Graph.h
        src/DataLoader.h
        src/DataHandler.h
        #...
)

set(CPP_FILES
        #...
        src/main.cpp
        src/Reservoir.cpp
        src/City.cpp
        src/NodeInfo.cpp
        src/Vertex.cpp
        src/Edge.cpp
        src/Graph.cpp
        src/DataLoader.cpp
        src/DataHandler.cpp
)

add_executable(water-supply-analysis
        ${H_FILES}
        ${CPP_FILES}
        src/menu/utils)