#Основная часть проекта, реализующая функционал
#Папки для сборки модуля
set(CMAKE_GDAL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_GDAL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_GDAL_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

get_property(POSTGRES_SRC_DIR GLOBAL PROPERTY POSTGRES_SRC_DIR)
get_property(POSTGRES_BIN_DIR GLOBAL PROPERTY POSTGRES_BIN_DIR)

#Папки с рекурсивным включением исходников
list(APPEND RECUSIVE_SRC_DIR
	/gcore
	/alg
	/apps
	/gnm
	/port
	/ogr/ogrsf_frmts/avc
	/ogr/ogrsf_frmts/cad
	/ogr/ogrsf_frmts/csv
	#/ogr/ogrsf_frmts/dwg нужно добавить библиотеку https://github.com/h4ck3rm1k3/InDirectDWG
	/ogr/ogrsf_frmts/dxf
	/ogr/ogrsf_frmts/geojson
	/ogr/ogrsf_frmts/generic
	/ogr/ogrsf_frmts/gml
	/ogr/ogrsf_frmts/kml
	/ogr/ogrsf_frmts/mem
	/ogr/ogrsf_frmts/mitab
	#/ogr/ogrsf_frmts/mssqlspatial
	/ogr/ogrsf_frmts/pg
	/ogr/ogrsf_frmts/pgdump
	/ogr/ogrsf_frmts/shape
	/ogr/ogrsf_frmts/svg
	/ogr/ogrsf_frmts/xplane
)

#Папки с включением исходников без захода во вложенные папки
list(APPEND NONE_RECUSIVE_SRC_DIR
				/frmts
				/ogr
				/ogr/ogrsf_frmts
)

#Список поддерживаемых форматов данных
list(APPEND FORMAT_LIST
	aaigrid adrg aigrid airsar arg
	blx bmp bsb #bpg
	cals ceos ceos2 coasp cosar ctg
	derived dimap #dods dds
	e00grid elas envisat ers #ecw epsilon
	fit #fits
	gff gif grib gsg gtiff gxf #georaster grass gta
	hfa hf2 #hdf5
	idrisi ilwis ingr iris iso8211
	jaxapalsar jdem jpeg #jp2lura jpeg2000 jp2kak jpegls jpipkak
	#kea kmlsuperoverlay
	l1b leveller
	map mmbtilles mem msp #mrf mrsid mrsid_lidar msgn
	ngsgeoid nitf northwood #netcdf
	o ozi #ogdi openjpeg
	pcraster pdf pds plmosaic png postgisraster prf #pcidsk
	r rasterlite raw rik rmf rs2 #rasdaman
	safe saga sentinel2 sgi srtmhgt #sdes sdts
	terragen til tsx
	usgsdem
	vrt
	wcs wms wmst #webp
	xpm xyz
	zlib zmap
)

foreach(format ${FORMAT_LIST})
	list(APPEND RECUSIVE_SRC_DIR /frmts/${format})
	list(APPEND FORMAT_INCLUDE ${CMAKE_GDAL_SOURCE_DIR}/frmts/${format})
endforeach()

foreach(row ${RECUSIVE_SRC_DIR})
	list(APPEND RECUSIVE_SRC ${CMAKE_GDAL_SOURCE_DIR}${row}/*.cpp ${CMAKE_GDAL_SOURCE_DIR}${row}/*.c)
endforeach()

foreach(row ${NONE_RECUSIVE_SRC_DIR})
	list(APPEND NONE_RECUSIVE_SRC ${CMAKE_GDAL_SOURCE_DIR}${row}/*.cpp ${CMAKE_GDAL_SOURCE_DIR}${row}/*.c)
endforeach()
file(GLOB_RECURSE GDAL_SRC_R RELATIVE "${CMAKE_GDAL_SOURCE_DIR}" ${RECUSIVE_SRC})
file(GLOB GDAL_SRC_N RELATIVE "${CMAKE_GDAL_SOURCE_DIR}" ${NONE_RECUSIVE_SRC})

set(GDAL_INCLUDE_DIRS
		${CMAKE_GDAL_SOURCE_DIR}/gen_include
		${CMAKE_GDAL_SOURCE_DIR}/alg
		${CMAKE_GDAL_SOURCE_DIR}/apps
		${CMAKE_GDAL_SOURCE_DIR}/gnm
		${CMAKE_GDAL_SOURCE_DIR}/gnm/gnm_frmts
		${CMAKE_GDAL_SOURCE_DIR}/alg/internal_libqhull
		${CMAKE_GDAL_SOURCE_DIR}/port
		${CMAKE_GDAL_SOURCE_DIR}/gcore
		${CMAKE_GDAL_SOURCE_DIR}/apps
		${CMAKE_GDAL_SOURCE_DIR}/frmts
		${CMAKE_GDAL_SOURCE_DIR}/frmts/gtiff/libtiff
		${CMAKE_GDAL_SOURCE_DIR}/frmts/jpeg/libjpeg
		${CMAKE_GDAL_SOURCE_DIR}/frmts/gtiff/libgeotiff
		${CMAKE_GDAL_SOURCE_DIR}/frmts/gif/giflib
		${CMAKE_GDAL_SOURCE_DIR}/frmts/grib/degrib18/degrib
		${CMAKE_GDAL_SOURCE_DIR}/frmts/grib/degrib18/g2clib-1.0.4
		${CMAKE_GDAL_SOURCE_DIR}/frmts/mrf/libLERC
		#${CMAKE_GDAL_SOURCE_DIR}/frmts/pcidsk/sdk
		${CMAKE_GDAL_SOURCE_DIR}/frmts/pcraster/libcsf
		${CMAKE_GDAL_SOURCE_DIR}/frmts/png/libpng
		${FORMAT_INCLUDE}
		${CMAKE_GDAL_SOURCE_DIR}/ogr
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/avc
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/cad/libopencad
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/kml
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/mem
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/generic
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/geojson
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/geojson/libjson
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/pgdump
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/shape
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/xplane
)
set_property(GLOBAL PROPERTY GDAL_INCLUDE_DIRS ${GDAL_INCLUDE_DIRS})
include_directories(${GDAL_INCLUDE_DIRS})

configure_file("${CMAKE_GDAL_SOURCE_DIR}/config.h.in" ${CMAKE_GDAL_SOURCE_DIR}/gen_include/cmake_config.h)
#Включаем CMake конфигурацию вместо make
add_definitions(-DCMAKE_CONFIG)
add_library(gdal STATIC ${GDAL_SRC_R} ${GDAL_SRC_N})
##Модульные зависимости
#add_dependencies(gdal SFCGAL)
target_link_libraries(gdal pq sfcgal geos-static)
##Берем заголовки напрямую из модуля GEOS
get_property(GEOS_INCLUDE_DIRS GLOBAL PROPERTY GEOS_INCLUDE_DIRS)
message("GEOS DIRS ${GEOS_INCLUDE_DIRS}")
include_directories(${GEOS_INCLUDE_DIRS})

get_property(SFCGAL_INCLUDE_DIRS GLOBAL PROPERTY SFCGAL_INCLUDE_DIRS)
message("SFCGAL DIRS ${SFCGAL_INCLUDE_DIRS}")
include_directories(${SFCGAL_INCLUDE_DIRS})

include_directories(${POSTGRES_SRC_DIR}/src/include ${POSTGRES_SRC_DIR}/src/interfaces/libpq)

#Добавление внешней библиотеки CURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(gdal ${CURL_LIBRARIES})

#Добавляем библиотеку динамической линковки DL
find_package(LibDL REQUIRED)
include_directories(${LIBDL_INCLUDE_DIR})
target_link_libraries(gdal ${LIBDL_LIBRARIES})

#Добавляем XML парсер
include(FindEXPAT)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})
target_link_libraries(gdal ${EXPAT_LIBRARIES})
