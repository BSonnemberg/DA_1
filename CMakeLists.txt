cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 11)
project(water-supply-analysis)

set(UTILS
        src/menu/utils/color.h
        src/menu/utils/printable.h
        src/menu/utils/printable.cpp
        src/menu/utils/scannable.h
        src/menu/utils/scannable.cpp
        src/menu/utils/termutils.h
        src/menu/utils/termutils.cpp
        src/menu/utils/textbox.h
        src/menu/utils/textbox.cpp
)

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
        src/menu/Menu.h
        src/menu/DatasetMenu.h
)

set(CPP_FILES
        src/main.cpp
        src/Reservoir.cpp
        src/City.cpp
        src/NodeInfo.cpp
        src/Vertex.cpp
        src/Edge.cpp
        src/Graph.cpp
        src/DataLoader.cpp
        src/DataHandler.cpp
        src/menu/MenuHandler.cpp
        src/menu/DatasetMenu.cpp
)

add_executable(water-supply-analysis
        ${UTILS}
        ${H_FILES}
        ${CPP_FILES})
