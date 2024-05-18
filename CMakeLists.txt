cmake_minimum_required(VERSION 3.20)

project(nm_spline VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(NO_GUI "specify to build w/o gui part" OFF)
option(X11 "Use this option if you have X11" OFF)
option(MAC "Use this option if you have MAC"  OFF)


if(${X11})
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Charts)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)
endif()

if(${MAC})
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Charts)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)
endif()

if(NOT ${X11} AND NOT ${MAC})
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets WaylandCompositor Charts)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets WaylandCompositor Charts)
endif()

add_subdirectory(src)
