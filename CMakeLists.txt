cmake_minimum_required(VERSION 3.5)

project(Monitoring_System)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Core Network Widgets REQUIRED)

set(SOURCES
    main.cpp
    Autorization.cpp
    Menu.cpp
    NetworkAction.cpp
    Network_traffic.cpp
    Host_stats.cpp
)

set(HEADERS
    Autorization.h
    Menu.h
    NetworkAction.h
    Network_traffic.h
    Host_stats.h
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(Monitoring_System ${SOURCES} ${MOC_SOURCES})

target_link_libraries(Monitoring_System Qt5::Core Qt5::Network Qt5::Widgets)