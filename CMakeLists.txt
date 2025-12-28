cmake_minimum_required(VERSION 3.16)
project(SmartHome LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Qml QuickControls2)

add_executable(smarthome
    src/main.cpp
    src/devicesmodel.cpp
    src/devicemanager.cpp
    qml.qrc
)

target_include_directories(smarthome PRIVATE src)

target_link_libraries(smarthome PRIVATE Qt6::Quick Qt6::Qml Qt6::QuickControls2)

qt_import_qml_plugins(smarthome)

install(TARGETS smarthome RUNTIME DESTINATION bin)
