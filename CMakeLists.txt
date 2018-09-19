# cmake -G "Visual Studio 15 2017 Win64" -DQt5Widgets_DIR=C:\Qt\Qt5.11.1\5.11.1\msvc2017_64\lib\cmake\Qt5Widgets -DQt5Network_DIR=C:\Qt\Qt5.11.1\5.11.1\msvc2017_64\lib\cmake\Qt5Network -DQT_HOME=C:\Qt\Qt5.11.1\5.11.1\msvc2017_64\bin ../
cmake_minimum_required(VERSION 3.1.0)
project(QtAppUpdate VERSION 1.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
set (app_src src/Downloader.ui src/Downloader.cpp src/QSimpleUpdater.cpp src/Updater.cpp src/main.cpp  src/Window.cpp src/Window.ui resources/qsimpleupdater.qrc)
add_executable(QtAppUpdate WIN32 ${app_src})
qt5_use_modules(QtAppUpdate Widgets)
qt5_use_modules(QtAppUpdate Network)
set_target_properties( QtAppUpdate
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_include_directories(QtAppUpdate PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/)
target_compile_definitions(QtAppUpdate PRIVATE PROJECT_VERSION=\"${PROJECT_VERSION}\")

install(DIRECTORY $<TARGET_FILE_DIR:QtAppUpdate> DESTINATION bin)
# add_definitions(-DPROJECT_VERSION=${PROJECT_VERSION})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CPACK_GENERATOR NSIS)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
SET(CPACK_NSIS_MODIFY_PATH ON)
include(cpack)

find_file(WINDEPLOYQT windeployqt.exe PATHS ${QT_HOME})
if(WINDEPLOYQT)
  message(STATUS "using ${WINDEPLOYQT}")
else(WINDEPLOYQT)
  message(FATAL_ERROR "WINDEPLOYQT not found")
endif(WINDEPLOYQT)
add_custom_target(pre-package COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_FILE:QtAppUpdate>"
COMMAND ${WINDEPLOYQT} --dir $<TARGET_FILE_DIR:QtAppUpdate> $<TARGET_FILE:QtAppUpdate>
COMMENT "pre package")
