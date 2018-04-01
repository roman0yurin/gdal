cmake_minimum_required(VERSION 3.5)
project(GdalModule C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)

##Добавки на время отладки
add_subdirectory(../geos ${CMAKE_CURRENT_BINARY_DIR}/geos)
add_subdirectory(../cgal ${CMAKE_CURRENT_BINARY_DIR}/cgal)
add_subdirectory(../sfcgal ${CMAKE_CURRENT_BINARY_DIR}/sfcgal)

add_subdirectory(gdal)


