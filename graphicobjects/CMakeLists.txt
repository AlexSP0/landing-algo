set(SOURCES point.cpp
            graphicalobject.cpp)
set(HEADERS point.h
            graphicalobject.h)
ADD_LIBRARY(graphicobjects STATIC ${HEADERS} ${SOURCES})
