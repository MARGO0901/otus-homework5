cmake_minimum_required(VERSION 3.16)

project(canvas2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    circle.cpp circle.h
    rect.cpp rect.h
    figure.cpp figure.h
)

add_executable(canvas2
    ${PROJECT_SOURCES}
)

target_link_libraries(canvas2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(canvas2 PRIVATE ${CMAKE_SOURCE_DIR}/include)
