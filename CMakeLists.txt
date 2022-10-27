cmake_minimum_required(VERSION 3.23)

project(qml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	renderwindow.cpp
	renderwindow.h
)

find_package(Qt6 CONFIG COMPONENTS Quick Widgets 3DCore)
find_package(SFML CONFIG COMPONENTS system graphics window)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt::Quick
	Qt::3DCore
	Qt::Widgets
	OpenGL32
	sfml-system
	sfml-graphics
	sfml-window
)
