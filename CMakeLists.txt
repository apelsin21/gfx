cmake_minimum_required(VERSION 2.8)
project(gfx)

#libraries that can be found in default path in linux
#install through package manager
set(LIBRARIES
    GLEW
    freeimage
    assimp
    GL
    GLU
)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
find_package(Freetype REQUIRED)

set(CMAKE_CXX_FLAGS " -std=c++11")

include_directories(${SDL2_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
