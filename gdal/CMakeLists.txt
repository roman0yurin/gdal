#Основная часть проекта, реализующая функционал
#Папки для сборки модуля
set(CMAKE_GDAL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_GDAL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE ALG_SRC RELATIVE "${CMAKE_GDAL_SOURCE_DIR}"
		"${CMAKE_GDAL_SOURCE_DIR}/gcore/*.cpp"
		"${CMAKE_GDAL_SOURCE_DIR}/gcore/*.c"
		"${CMAKE_GDAL_SOURCE_DIR}/alg/*.cpp"
		"${CMAKE_GDAL_SOURCE_DIR}/alg/*.c"
		"${CMAKE_GDAL_SOURCE_DIR}/ogr/*.cpp"
		"${CMAKE_GDAL_SOURCE_DIR}/ogr/*.c"
		)

include_directories(
		${CMAKE_GDAL_SOURCE_DIR}/gen_include
		${CMAKE_GDAL_SOURCE_DIR}/alg
		${CMAKE_GDAL_SOURCE_DIR}/alg/internal_libqhull
		${CMAKE_GDAL_SOURCE_DIR}/port
		${CMAKE_GDAL_SOURCE_DIR}/gcore
		${CMAKE_GDAL_SOURCE_DIR}/apps
		${CMAKE_GDAL_SOURCE_DIR}/frmts
		${CMAKE_GDAL_SOURCE_DIR}/frmts/mem
		${CMAKE_GDAL_SOURCE_DIR}/frmts/gtiff
		${CMAKE_GDAL_SOURCE_DIR}/frmts/vrt
		${CMAKE_GDAL_SOURCE_DIR}/ogr
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/mem
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/generic
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/geojson
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/geojson/libjson
)
file(GLOB_RECURSE ALG_HEADERS RELATIVE "${CMAKE_GDAL_SOURCE_DIR}"
		"${CMAKE_GDAL_SOURCE_DIR}/alg/*.h"
		"${CMAKE_GDAL_SOURCE_DIR}/alg/*.hpp"
		)

configure_file("${CMAKE_GDAL_SOURCE_DIR}/config.h.in" ${CMAKE_GDAL_SOURCE_DIR}/gen_include/cmake_config.h)
#Включаем CMake конфигурацию вместо make
add_definitions(-DCMAKE_CONFIG)
add_library(gdal STATIC ${ALG_SRC})
##Модульные зависимости
add_dependencies(gdal SFCGAL)
target_link_libraries(gdal sfcgal geos)
##Берем заголовки напрямую из модуля GEOS
get_property(GEOS_INCLUDE_DIRS GLOBAL PROPERTY GEOS_INCLUDE_DIRS)
message("GEOS DIRS ${GEOS_INCLUDE_DIRS}")
include_directories(${GEOS_INCLUDE_DIRS})

get_property(SFCGAL_INCLUDE_DIRS GLOBAL PROPERTY SFCGAL_INCLUDE_DIRS)
message("SFCGAL DIRS ${SFCGAL_INCLUDE_DIRS}")
include_directories(${SFCGAL_INCLUDE_DIRS})
