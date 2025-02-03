cmake_minimum_required(VERSION 3.5)

project(Monitoring_System)

set(CMAKE_CXX_STANDARD 14)

# Найти и подключить библиотеки Qt5
find_package(Qt5 COMPONENTS Core Network Widgets Sql Charts REQUIRED)

# Найти и подключить библиотеку PostgreSQL
find_package(PostgreSQL REQUIRED)

if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 not found!")
endif()

if(NOT PostgreSQL_FOUND)
    message(FATAL_ERROR "PostgreSQL not found!")
endif()

# Исходные файлы проекта
set(SOURCES
    main.cpp
    Autorization.cpp
    Menu.cpp
    AddForm.cpp
    Server_logs.cpp
    NetworkAction.cpp
    Host_stats.cpp
    Host_window.cpp
    db_connection.cpp
    DiskUsageWidget.cpp
    CpuUsageWidget.cpp
    MemUsageWidget.cpp
)

# Заголовочные файлы проекта
set(HEADERS
    Autorization.h
    Menu.h
    AddForm.h
    Server_logs.h
    NetworkAction.h
    Host_stats.h
    Host_window.h
    DiskUsageWidget.h
    CpuUsageWidget.h
    MemUsageWidget.h
)

# Генерация MOC файлов для Qt
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Создание исполняемого файла
add_executable(Monitoring_System ${SOURCES} ${MOC_SOURCES})

# Включение директорий заголовочных файлов Qt5 и PostgreSQL
target_include_directories(Monitoring_System PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})

# Подключение библиотек Qt5 и PostgreSQL к проекту
target_link_libraries(Monitoring_System Qt5::Core Qt5::Network Qt5::Widgets Qt5::Sql Qt5::Charts ${PostgreSQL_LIBRARIES})