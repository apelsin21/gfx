set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/referencecounted.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/device.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sdl2window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/window.cpp
	
    #gui
	#scene
    #game
 
    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
    #core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/referencecounted.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/device.hpp

	#gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/drivertype.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sdl2window.hpp

	#gui
	#scene
    #game
	
    PARENT_SCOPE
)
