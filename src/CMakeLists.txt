set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/referencecounted.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/device.cpp

    #gfx
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
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/drivertypes.hpp

	#gui
	#scene
    #game
	
    PARENT_SCOPE
)
