cmake_minimum_required(VERSION 3.8)

project(app CXX)

set(CMAKE_CXX_STANDARD 17)

set(APP_DIR "${CMAKE_CURRENT_LIST_DIR}")

find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtkmm-3.0)
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_executable(app main.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_library(application3D include/application3D.cpp)
add_library(meta include/meta.cpp)

target_link_libraries(app meta application3D sfml-graphics sfml-audio ${GTK3_LIBRARIES})

