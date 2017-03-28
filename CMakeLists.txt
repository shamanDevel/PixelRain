cmake_minimum_required(VERSION 3.0)

project(PixelRain)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOIL_SOURCES 
	SOIL/image_DXT.c
	SOIL/image_helper.c
	SOIL/stb_image_aug.c
	SOIL/SOIL.c)
set(SOIL_HEADERS
	SOIL/image_DXT.h
	SOIL/image_helper.h
	SOIL/stb_image_aug.h
	SOIL/SOIL.h)

set(SOURCE_FILES 
	src/main.cpp)
set(HEADER_FILES 
	include/pixelrain.h 
	include/pixelrain_defaults.h
	include/vector.h)
source_group("Headers" FILES ${HEADER_FILES})
source_group("Soil" FILES ${SOIL_SOURCES} ${SOIL_HEADERS})
add_executable(pixelrain 
	${SOURCE_FILES} ${HEADER_FILES}
	${SOIL_SOURCES} ${SOIL_HEADERS})
target_include_directories(pixelrain PUBLIC include SOIL)