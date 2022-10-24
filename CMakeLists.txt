cmake_minimum_required(VERSION 3.23)

project(qml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

find_package(Qt6 CONFIG COMPONENTS Quick Widgets 3DCore)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt::Quick
	Qt::3DCore
	Qt::Widgets
)
