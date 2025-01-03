cmake_minimum_required(VERSION 3.10)

# Project name
project(Monitoring_System)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# QtWidgets is required for GUI applications
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

# Add the executable
add_executable(Monitoring_System main.cpp)

# Link Qt libraries
target_link_libraries(Monitoring_System Qt5::Widgets Qt5::Network)
