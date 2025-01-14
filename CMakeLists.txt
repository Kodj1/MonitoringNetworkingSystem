cmake_minimum_required(VERSION 3.5)

project(Monitoring_System)

set(CMAKE_CXX_STANDARD 14)

# Найти и подключить библиотеки Qt5
find_package(Qt5 COMPONENTS Core Network Widgets Sql REQUIRED)

# Найти и подключить библиотеку PostgreSQL
find_package(PostgreSQL REQUIRED)

# Исходные файлы проекта
set(SOURCES
    main.cpp
    Autorization.cpp
    Menu.cpp
    NetworkAction.cpp
    Network_traffic.cpp
    Host_stats.cpp
    Host_window.cpp
)

# Заголовочные файлы проекта
set(HEADERS
    Autorization.h
    Menu.h
    NetworkAction.h
    Network_traffic.h
    Host_stats.h
    Host_window.h
)

# Генерация MOC файлов для Qt
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Создание исполняемого файла
add_executable(Monitoring_System ${SOURCES} ${MOC_SOURCES})

# Включение директорий заголовочных файлов Qt5 и PostgreSQL
target_include_directories(Monitoring_System PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})

# Подключение библиотек Qt5 и PostgreSQL к проекту
target_link_libraries(Monitoring_System Qt5::Core Qt5::Network Qt5::Widgets Qt5::Sql ${PostgreSQL_LIBRARIES})