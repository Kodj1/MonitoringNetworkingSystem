cmake_minimum_required(VERSION 3.5)

project(Monitoring_System)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Qt5Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)