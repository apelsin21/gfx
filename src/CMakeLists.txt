set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keys.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.cpp
	
    #gui
	#scene
    #game
 
    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
    #core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/windowevent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keyboardkeys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/mousekeys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keys.hpp

	#gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.hpp

	#gui
	#scene
    #game
	
    PARENT_SCOPE
)
