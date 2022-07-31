find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core)

set(SOURCES point.cpp
            graphicalobject.cpp
            testfigure.cpp)
set(HEADERS point.h
            graphicalobject.h
            testfigure.h)

ADD_LIBRARY(graphicobjects STATIC ${HEADERS} ${SOURCES})

target_link_libraries(graphicobjects PRIVATE Qt5::Widgets Qt5::Core)
