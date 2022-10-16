find_package(Qt5 REQUIRED COMPONENTS Core)

set(SOURCES
    sneuron.cpp
    sneuronlayer.cpp
    sneuralnet.cpp
    nlink.h
)
set(HEADERS
    sneuron.h
    sneuronlayer.h
    sneuralnet.h
)


ADD_LIBRARY(neuronet STATIC ${HEADERS} ${SOURCES})

target_link_libraries(neuronet PRIVATE Qt5::Core)
