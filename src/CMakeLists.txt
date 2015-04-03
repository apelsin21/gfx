set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/free_image_texture.cpp
	
    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
    #core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window_event.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keyboard_keys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/mouse_keys.hpp

	#gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/free_image_texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.hpp

    PARENT_SCOPE
)
