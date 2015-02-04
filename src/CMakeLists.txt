set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/referencecounted.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/device.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sdl2window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sdl2keys.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/driver.cpp
	
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
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/windowevent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/keyboardkeys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/mousekeys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sdl2window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sdl2keys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/driver.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/modernopengldriver.hpp

	#gui
	#scene
    #game
	
    PARENT_SCOPE
)
