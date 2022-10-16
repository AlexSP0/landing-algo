cmake_minimum_required(VERSION 3.5)

project(landing-algo VERSION 0.1 LANGUAGES CXX)

add_subdirectory(graphicobjects)
add_subdirectory(gameobjects)
add_subdirectory(neuronet)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        gamewindow.h
        gamewindow.cpp
        gamewindow.ui
        constants.h
)

add_executable(landing-algo ${PROJECT_SOURCES})

target_link_libraries(landing-algo PRIVATE Qt5::Widgets Qt5::Core)
target_link_libraries(landing-algo PRIVATE graphicobjects)
target_link_libraries(landing-algo PRIVATE gameobjects)
target_link_libraries(landing-algo PRIVATE neuronet)
