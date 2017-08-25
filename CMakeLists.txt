cmake_minimum_required(VERSION 2.6)
project(qtCannelloniCanBusPlugin)

ADD_DEFINITIONS(
  -std=c++14
  -Wall
  )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

include_directories(../)

add_library(${PROJECT_NAME} SHARED
  QtCannelloniCanBusPlugin.cpp
  CannelloniCanBackend.cpp
  )

target_link_libraries(${PROJECT_NAME} Qt5::Core)
