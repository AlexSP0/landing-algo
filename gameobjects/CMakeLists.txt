find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    lander.cpp
    genome.cpp
    genealgo.cpp
    genecontroller.cpp
)

set(HEADERS
    lander.h
    constants.h
    genome.h
    genealgo.h
    genecontroller.h
)

ADD_LIBRARY(gameobjects STATIC ${SOURCES} ${HEADERS})

target_link_libraries(gameobjects PRIVATE Qt5::Widgets Qt5::Core graphicobjects neuronet)

