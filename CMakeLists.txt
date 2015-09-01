cmake_minimum_required(VERSION 2.8)
project(gfx)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_CXX_FLAGS "-std=c++14")

find_path(FREETYPE_INCLUDE_DIRS freetype/freetype.h HINTS /usr/include/freetype2)
include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(Bullet REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(OPUSFILE REQUIRED opusfile)
pkg_search_module(EPOXY REQUIRED epoxy)

include_directories(
	${OPENGL_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
	${BULLET_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIRS}
	${EPOXY_INCLUDE_DIRS}
	${OPUS_INCLUDE_DIRS}
	/usr/include/opus
	${SDL2_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(
	${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${SOURCES}
	${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
	${EPOXY_LIBRARIES}
	${OPENGL_LIBRARY}
	${OPENAL_LIBRARY}
	${BULLET_LIBRARY}
	freeimage
	${FREETYPE_LIBRARIES}
	${FREEIMAGE_LIBRARIES}
	opus
	opusfile
	${SDL2_LIBRARIES}
)
