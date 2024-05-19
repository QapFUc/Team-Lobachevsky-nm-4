
set( PROJECT_SOURCES
    main.cpp
    widget.cpp
)


add_executable( gui.out
                ${PROJECT_SOURCES}
)


option(X11 "Use this option if you have X11" OFF)
option(MAC "Use this option if you have MAC"  OFF)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Charts REQUIRED)


if(${X11})
    target_link_libraries(gui.out PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)
endif()

if(${MAC})
    target_link_libraries(gui.out PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)
endif()

if(NOT ${X11} AND NOT ${MAC})
    target_link_libraries(gui.out PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WaylandCompositor Qt${QT_VERSION_MAJOR}::Charts)
endif()