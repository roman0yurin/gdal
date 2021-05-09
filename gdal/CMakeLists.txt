#Основная часть проекта, реализующая функционал
#Папки для сборки модуля
set(CMAKE_GDAL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_GDAL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_GDAL_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

##Когда данная библиотека входит в сборку POSTGIS то указанные библиотеки присутствуют как модули
if(INSIDE_POSTGIS)
	set(HAVE_SFCGAL 1)
	set(HAVE_GEOS 1)
	set(HAVE_PG 1)
	set(HAVE_LIBJPEG 1)
	#Список поддерживаемых форматов данных
	list(APPEND FORMAT_LIST postgisraster wms wmst )

	list(APPEND RECUSIVE_SRC_DIR /ogr/ogrsf_frmts/pg)

endif()
set(HAVE_EXPAT 1)

get_property(POSTGRES_SRC_DIR GLOBAL PROPERTY POSTGRES_SRC_DIR)
get_property(POSTGRES_BIN_DIR GLOBAL PROPERTY POSTGRES_BIN_DIR)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpsapi")
endif()

configure_file("${CMAKE_GDAL_SOURCE_DIR}/gcore/gdal_version.h.in" ${CMAKE_GDAL_SOURCE_DIR}/gcore/gdal_version.h)


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
	#/ogr/ogrsf_frmts/pg
	/ogr/ogrsf_frmts/pgdump
	/ogr/ogrsf_frmts/shape
	/ogr/ogrsf_frmts/svg
	/ogr/ogrsf_frmts/xplane
	/ogr/ogrsf_frmts/vrt
)

#Исключаемые из сборки исходники, относительный путь
list(APPEND EXCLUDE_SOURCES
		apps/ogrdissolve.cpp
		apps/testreprojmulti.cpp
		apps/gdal2ogr.c
		frmts/bsb/bsb2raw.c
		frmts/ceos/ceostest.c
		frmts/envisat/dumpgeo.c
		frmts/envisat/envisat_dump.c
		frmts/gtiff/generate_quant_table_md5sum.cpp
		frmts/hfa/hfatest.cpp
		frmts/iso8211/8211createfromxml.cpp
		frmts/iso8211/8211dump.cpp
		frmts/iso8211/8211view.cpp
		frmts/iso8211/mkcatalog.cpp
		frmts/iso8211/timetest.cpp
		frmts/nitf/nitfdump.c
		ogr/ogrsf_frmts/shape/dbfopen_wrapper.c
		ogr/ogrsf_frmts/shape/sbnsearch_wrapper.c
		ogr/ogrsf_frmts/shape/shpopen_wrapper.c
		ogr/ogrsf_frmts/shape/shptree_wrapper.c
		port/xmlreformat.cpp
		ogr/generate_encoding_table.c
		ogr/ogr_capi_test.c
		ogr/test_geo_utils.cpp
		frmts/aigrid/aitest.c
		apps/gdal_contour.cpp
		apps/gdal_create.cpp
		apps/gdal_grid_bin.cpp
		apps/gdal_rasterize_bin.cpp
		apps/gdal_translate_bin.cpp
		apps/gdal_viewshed.cpp
		apps/gdaladdo.cpp
		apps/gdalasyncread.cpp
		apps/gdalbuildvrt_bin.cpp
		apps/gdaldem_bin.cpp
		apps/gdalenhance.cpp
		apps/gdalflattenmask.c
		apps/gdalinfo_bin.cpp
		apps/gdallocationinfo.cpp
		apps/gdalmanage.cpp
		apps/gdalmdiminfo_bin.cpp
		apps/gdalmdimtranslate_bin.cpp
		apps/gdalsrsinfo.cpp
		apps/gdaltindex.cpp
		apps/gdaltorture.cpp
		apps/gdaltransform.cpp
		apps/gdalwarp_bin.cpp
		apps/gdalwarpsimple.c
		apps/gnmanalyse.cpp
		apps/gnmmanage.cpp
		apps/multireadtest.cpp
		apps/nearblack_bin.cpp
		apps/ogr2ogr_bin.cpp
		apps/ogrinfo.cpp
		apps/ogrlineref.cpp
		apps/ogrtindex.cpp:100
		apps/test_ogrsf.cpp
		apps/testepsg.cpp
		apps/ogrtindex.cpp
		apps/dumpoverviews.cpp
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
	pcraster pdf pds plmosaic png prf #pcidsk
	r rasterlite raw rik rmf rs2 #rasdaman
	safe saga sentinel2 sgi srtmhgt #sdes sdts
	terragen til tsx
	usgsdem
	vrt
	wcs #webp
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

list(APPEND SOURCES_LIST ${GDAL_SRC_R} ${GDAL_SRC_N})
list(REMOVE_ITEM SOURCES_LIST ${EXCLUDE_SOURCES})

set(GDAL_INCLUDE_DIRS
		${CMAKE_GDAL_SOURCE_DIR}/gen_include
		${CMAKE_GDAL_SOURCE_DIR}/alg
		${CMAKE_GDAL_SOURCE_DIR}/alg/marching_squares
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
		${CMAKE_GDAL_SOURCE_DIR}/frmts/grib/degrib/g2clib
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/vrt
		${CMAKE_GDAL_SOURCE_DIR}/ogr/ogrsf_frmts/gml
)

set_property(GLOBAL PROPERTY GDAL_INCLUDE_DIRS ${GDAL_INCLUDE_DIRS})
include_directories(${GDAL_INCLUDE_DIRS})

configure_file("${CMAKE_GDAL_SOURCE_DIR}/config.h.in" ${CMAKE_GDAL_SOURCE_DIR}/gen_include/cmake_config.h)
#Включаем CMake конфигурацию вместо make
add_definitions(-DCMAKE_CONFIG)

add_library(gdal STATIC ${SOURCES_LIST})
set_property(TARGET gdal PROPERTY POSITION_INDEPENDENT_CODE ON)

#Добавляем тест для проверки GDAL
add_executable(VitaliyTest ${SOURCES_LIST} main.cpp)
set_property(TARGET VitaliyTest PROPERTY POSITION_INDEPENDENT_CODE ON)

#Добавление внешней библиотеки CURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(gdal ${CURL_LIBRARIES})
target_link_libraries(VitaliyTest ${CURL_LIBRARIES})

#Добавляем библиотеку динамической линковки DL
find_package(LibDL REQUIRED)
include_directories(${LIBDL_INCLUDE_DIR})
target_link_libraries(gdal ${LIBDL_LIBRARIES})
target_link_libraries(VitaliyTest ${LIBDL_LIBRARIES})

#Добавляем XML парсер
include(FindEXPAT)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})
target_link_libraries(gdal ${EXPAT_LIBRARIES})
target_link_libraries(VitaliyTest ${EXPAT_LIBRARIES})


#Добавляем библиотеку прекций LibPoj4
find_package(Proj REQUIRED)
include_directories(${PROJ_INCLUDE_DIR})
#При необходимости можно добавить ее и к статичесой библиотеке, если она не собирается из исходников
message(">>>>>>> ${PROJ_LIBRARY}")
target_link_libraries(VitaliyTest ${PROJ_LIBRARY})




