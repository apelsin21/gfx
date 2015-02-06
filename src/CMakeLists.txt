set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2keys.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/driver.cpp
	
    #gui
	#scene
    #game
 
    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
    #core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/device.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/windowevent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keyboardkeys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/mousekeys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2keys.hpp

	#gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/drivertype.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/driver.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/modernopengldriver.hpp

	#gui
	#scene
    #game
	
    PARENT_SCOPE
)
