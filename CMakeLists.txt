cmake_minimum_required(VERSION 2.8)
project(gfx)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

if(WIN32)
    #as this is windows, you'll have to provide
    #the path to these libraries
    set(LIBRARIES
        GLEW
        freeimage
        assimp
    )
    
    set(CMAKE_CXX_FLAGS " -std=c++11")

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
    
    add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${SOURCES} ${HEADERS})
    
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
endif(WIN32)

if(UNIX)
    #libraries that can be found in default path in unix
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
    
    add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${SOURCES} ${HEADERS})
    
    target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
endif(UNIX)
