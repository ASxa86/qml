cmake_minimum_required(VERSION 3.23)

project(qml)

find_package(Qt6 CONFIG COMPONENTS Quick Qml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(${PROJECT_NAME}
	main.cpp
)

set_source_files_properties(Actions.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(${PROJECT_NAME}
    URI qml
    QML_FILES
        main.qml
		DataBus.qml
        Actions.qml
        Store.qml
        Subscribe.qml
        View.qml
)

if(MSVC)
    set(VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${VCPKG_ROOT}/bin\nQT_PLUGIN_PATH=${VCPKG_ROOT}/Qt6/plugins\nQML_IMPORT_PATH=${VCPKG_ROOT}/Qt6/qml")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt::Quick
	Qt::Qml
)
